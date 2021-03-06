#!/bin/bash

declare -i pwrc__success=0
declare -i pwrc__dblocked=1
declare -i pwrc__loaddb=2
declare -i pwrc_status=$pwrc__success


snp_save_file()
{
  new_file=$1
  
  if [ -e $new_file ]; then
    let version=9

    while [ $version -ge 1 ]
    do
      old_file=$new_file.$version
      old_file_ren=$new_file.$((version+1))
      if [ -e $old_file ]; then
        mv $old_file $old_file_ren
      fi
      let version=$version-1
    done

    old_file=$new_file.1
    echo "-- Saving file $new_file -> $old_file"
    mv $new_file $old_file
  fi
}

#
# Get the databases in a project
#
# Arguments 1: project root
# Returns pwrc_status : 0 Success
#                   
#
pwrc_dblist_read()
{
  local volume
  local volid
  local volclass
  local volcnf
  local volenum
  local volserver
  local dbfile
  local db
  local proot=$1
  let i=0
  let j=0
  let k=0

  pwrc_status=$pwrc__success

  #set -o xtrace

  if [ -n "${db_array[*]}" ]; then
    unset db_array
  fi

  dbfile=$proot/src/db/pwrp_cnf_volumelist.dat
  if [ ! -e $dbfile ]; then
    echo "Can't find $dbfile"
    return
  fi

  while read volume volid volclass volcnf volenum volserver; do
    if [ -n "$volume" ] && [ "${volume:0:1}" != "!" ] && [ $volume != "$2" ]; then      
      if [ $volcnf == "cnf" ]; then
        if [ $volclass == "ClassVolume" ]; then
          if [ $volenum -eq 0 ]; then
            wbl_array[$k]=`eval echo $volume | tr "[:upper:]" "[:lower:]"`
            k=$k+1            
          elif [ $volenum -eq 1 ]; then
            db_array[$i]=`eval echo $volume | tr "[:upper:]" "[:lower:]"`
            i=$i+1
          elif [ $volenum -eq 2 ]; then
            dbms_array[$j]=`eval echo $volume | tr "[:upper:]" "[:lower:]"`
            dbms_server_array[$j]=$volserver
            j=$j+1
          fi
        else
          if [ $volenum -eq 0 ]; then
            db_array[$i]=`eval echo $volume | tr "[:upper:]" "[:lower:]"`
            i=$i+1
          elif [ $volenum -eq 1 ]; then
            dbms_array[$j]=`eval echo $volume | tr "[:upper:]" "[:lower:]"`
            dbms_server_array[$j]=$volserver
            j=$j+1
          fi
        fi
      fi
    fi
  done < $dbfile
}

action=$1
proot=$2
current_volume=$3

pwrc_dblist_read $proot $current_volume

# Check that no database is not locked
let i=0
while [ "${db_array[$i]}" != "" ]; do
  echo $i Database ${db_array[$i]}
  lockfile="$proot/src/db/${db_array[$((i++))]}.db.lock"
  echo $lockfile
  if [ -e $lockfile ]; then
    echo "Database is locked..."
    exit $pwrc__dblocked
  fi
done

if [ $action == "create" ]; then

  # Create revision files
  let i=0
  while [ "${db_array[$i]}" != "" ]; do
    wb_cmd -v ${db_array[$i]} wb dump/nofo/out=\"$proot/src/db/${db_array[$((i++))]}.wb_rev\"
  done

elif [ $action == "restore" ]; then

  # Load revision files

  # Rename old databases
  let i=0
  while [ "${db_array[$i]}" != "" ]; do
    snp_save_file $pwrp_db/${db_array[$i]}.db
    let $((i++))
  done

  while [ "${dbms_array[$i]}" != "" ]; do
    dbname="pwrp_"$pwrp_projectname"__"${dbms_array[$i]}
    mysqldump -h ${dbms_server_array[$i]} -upwrp $dbname > $pwrp_db/${dbms_array[$i]}.dbms/$dbname.mysqldump

    mysqladmin -h ${dbms_server_array[$i]} -upwrp drop -f $dbname

    snp_save_file $pwrp_db/${dbms_array[$i]}.dbms
    i=$i+1
  done

  # Load revision files
  let i=0
  while [ "${db_array[$i]}" != "" ]; do
    dump_file=$pwrp_db/${db_array[$i]}.wb_dmp
    list_file=$pwrp_db/${db_array[$((i++))]}.lis
    if wb_cmd -q wb load/nofocode/load=\"$dump_file\"/out=\"$list_file\"
    then
      echo "sts: ok $pwrc_status"
    else
      cat $list_file
      pwrc_status=$pwrc__loaddb
      echo "sts: no $pwrc_status"
    fi
  done
  echo sts: $pwrc_status
  exit $pwrc_status

fi
exit $pwrc__success
