include $(pwre_dir_symbols)

local_java_sources := \
	JopLog.java \
	Ge.java \
	PrintfFormat.java \
	GeCFormat.java \
	GeDyndata.java \
	GeColor.java \
	JopDynamic.java \
	LocalDb.java \
	JopCrypt.java \
	JopEngine.java \
	JopSessionIfc.java \
	JopUtilityIfc.java \
	JopUtility.java \
	JopSession.java \
	JopLang.java \
	JopMethods.java \
	JopMethodsMenu.java \
	JopConfirm.java \
	JopConfirmDialog.java \
	JopFrame.java \
	JopGrowFrame.java \
	JopApplet.java \
	JopSpider.java \
	Jop.java \
	GeComponentIfc.java \
	GeDynElemIfc.java \
	GeDyn.java \
	GeComponent.java \
	GeTextField.java \
	GeGradient.java \
	GeSlider.java \
	JopBar.java \
	JopTrend.java \
	JopAxis.java \
	JopAxisarc.java \
	JopPie.java \
	JopBarChart.java \
	GeTable.java \
	GeDynElem.java \
	GeDynDigLowColor.java \
	GeDynDigColor.java \
	GeDynDigError.java \
	GeDynDigWarning.java \
	GeDynDigFlash.java \
	GeDynInvisible.java \
	GeDynDigBorder.java \
	GeDynDigText.java \
	GeDynValue.java \
	GeDynRotate.java \
	GeDynMove.java \
	GeDynAnalogShift.java \
	GeDynDigShift.java \
	GeDynAnimation.java \
	GeDynSetDig.java \
	GeDynResetDig.java \
	GeDynToggleDig.java \
	GeDynStoDig.java \
	GeDynCommand.java \
	GeDynConfirm.java \
	GeDynIncrAnalog.java \
	GeDynRadioButton.java \
	GeDynPopupMenu.java \
	GeDynSlider.java \
	GeDynValueInput.java \
	GeDynAnalogColor.java \
	GeDynStatusColor.java \
	GeDynTipText.java \
	GeDynFillLevel.java \
	GeDynCloseGraph.java \
	GeDynPulldownMenu.java \
	GeDynOptionMenu.java \
	GeDynAnalogText.java \
	GeDynTable.java \
	GeDynHostObject.java \
	GeDynXYCurve.java \
	GeDynSetValue.java \
	JopXYCurve.java \
	Proportion.java\
	RatioLayout.java \
	JopCurveAxis.java \
	JopCurveAxisLayout.java \
	JopCurveChartLayout.java \
	AspectRatioListener.java \
	JopSpiderFrame.java \
	JopLoginFrame.java \
	JopLoginApplet.java \
	JopLanguageFrame.java \
	GeColorEditor.java \
	GeColorBrightnessEditor.java \
	GeColorToneEditor.java \
	GeColorShiftEditor.java \
	GeColorIntensityEditor.java \
	ClickActionEditor.java \
        JopUtilities.java \
        GeImage.java \
	GeFrameThin.java \
	Flow.java \
	FlowCtxInterface.java \
	FlowNodeIfc.java \
	FlowCmn.java \
	FlowComponent.java \
	FlowPoint.java \
	FlowArrayElem.java \
	FlowRect.java \
	FlowLine.java \
	FlowTriangle.java \
	FlowText.java \
	FlowArc.java \
	FlowArrow.java \
	FlowAnnot.java \
	FlowConPoint.java \
	FlowArray.java \
	FlowNodeClass.java \
	FlowConClass.java \
	FlowNode.java \
	FlowCon.java \
	FlowVector.java \
	FlowCtx.java \
	FlowFrame.java \
	CrrFrame.java \
	JopViewport.java \
	JopScrollPane.java \
	Logg.java \
	TreeObj.java \
	AttrObj.java \
	XttObjAttr.java \
	DynamicObj.java \
	XttRefObj.java \
	XttArrayAttr.java \
	XttObj.java \
	XttTree.java \
	JopXttApplet.java \
	JopXttFrame.java \
	JopCurveData.java \
	JopCurveIfc.java \
	JopCurve.java \
	JopXttTrend.java \
	JopXttFast.java \
        EventTableModel.java \
	EventTableCellRender.java \
	MhTable.java \
	MhClient.java \
        MhFrame.java \
        JopOpWindow.java \
        JopOpWindowFrame.java \
        JopOpWindowApplet.java \
	HistDateChooser.java \
	HistSender.java \
	HistStatModel1.java \
	HistStatModel2.java \
	HistStatistics.java \
	HistTable.java \
	HistStatModel1.java \
	HistStatModel2.java \
	HistStatistics.java \
	HistSearch.java \
	JopOp.java \
	JopSessionRep.java

-include $(pwre_kroot)/tools/bld/src/$(os_name)/$(hw_name)/$(type_name)_generic.mk

ifeq ($($(type_name)_generic_mk),)
 -include $(pwre_kroot)/tools/bld/src/$(os_name)/$(type_name)_generic.mk
endif

ifeq ($($(type_name)_generic_mk),)
 include $(pwre_kroot)/tools/bld/src/$(type_name)_generic.mk
endif

-include ../../special.mk
-include ../special.mk
-include special.mk

exe : $(doc_dir)/en_us/jprm/index.html

$(doc_dir)/en_us/jprm/index.html :
	@ echo "Generating javadoc for rt, jop and jopg"
	@ if [ ! -e $(doc_dir)/en_us/jprm ]; then mkdir $(doc_dir)/en_us/jprm; fi
	@ javadoc -Xdoclint:none -d $(doc_dir)/en_us/jprm $(pwre_sroot)/jpwr/rt/src/*.java $(pwre_sroot)/jpwr/jop/src/*.java $(pwre_sroot)/jpwr/jopg/src/*.java


