/* 
 * Proview   Open Source Process Control.
 * Copyright (C) 2005-2012 SSAB EMEA AB.
 *
 * This file is part of Proview.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation, either version 2 of 
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with Proview. If not, see <http://www.gnu.org/licenses/>
 *
 * Linking Proview statically or dynamically with other modules is
 * making a combined work based on Proview. Thus, the terms and 
 * conditions of the GNU General Public License cover the whole 
 * combination.
 *
 * In addition, as a special exception, the copyright holders of
 * Proview give you permission to, from the build function in the
 * Proview Configurator, combine Proview with modules generated by the
 * Proview PLC Editor to a PLC program, regardless of the license
 * terms of these modules. You may copy and distribute the resulting
 * combined work under the terms of your choice, provided that every 
 * copy of the combined work is accompanied by a complete copy of 
 * the source code of Proview (the version used to produce the 
 * combined work), being distributed under the terms of the GNU 
 * General Public License plus this exception.
 */


package jpwr.jopg;
import java.awt.font.*;

import android.app.Activity;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.DashPathEffect;
import android.graphics.LinearGradient;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.RadialGradient;
import android.graphics.Rect;
import android.graphics.RectF;
import android.graphics.Region;
import android.graphics.Shader;
import android.graphics.Typeface;
import android.renderscript.Font;

public class GlowDraw implements GlowDrawIfc {
    boolean nodraw = true;
	Typeface[] fonts = new Typeface[6];
	int canvasWidth;
	int canvasHeight;
    Activity activity;
    Canvas canvas;
    Paint paint;
    
    public GlowDraw() {
    	paint = new Paint();


    }
        
    public void setActivity(Activity activity) {
    	this.activity = activity;
    	fonts[0] = Typeface.create(Typeface.DEFAULT, Typeface.NORMAL);
		fonts[1] = Typeface.create(Typeface.DEFAULT, Typeface.BOLD);
		fonts[2] = Typeface.create(Typeface.SANS_SERIF, Typeface.NORMAL);
		fonts[3] = Typeface.create(Typeface.SANS_SERIF, Typeface.BOLD);
		fonts[4] = Typeface.createFromAsset(activity.getAssets(), "fonts/DroidSans.ttf");
		fonts[5] = Typeface.createFromAsset(activity.getAssets(), "fonts/DroidSans-Bold.ttf");
    }

    public void setNodraw(boolean nodraw) {
    	this.nodraw = nodraw;
    }

    public void setCanvas(Canvas canvas) {
    	this.canvas = canvas;	
    	nodraw = false;
    }

    public void rect(int border, int fill, double x, double y, double width, double height) {
    	if ( nodraw)
    		return;
		paint.setColor(Color.BLACK);
		paint.setStyle(Paint.Style.STROKE);
		paint.setStrokeWidth(1);
		canvas.drawRect((float)x, (float)y, (float)(x + width), (float)(y + height), paint);			
    }

    public void rect(int x, int y, int width, int height, int gc_type, int idx, int highlight) {
    	if ( nodraw)
    		return;

    	if ( gc_type == Glow.eDrawType_LineGray && highlight != 0)
    		gc_type = Glow.eDrawType_Line;

    	int color = getColor(gc_type);

    	paint.setColor(color);
    	paint.setStyle(Paint.Style.STROKE);
    	paint.setStrokeWidth(1);
    	canvas.drawRect((float)x, (float)y, (float)(x + width), (float)(y + height), paint);			
    }

    public void fill_rect(int x, int y, int width, int height, int gc_type) {
    	if ( nodraw)
    		return;

    	int color = getColor(gc_type);
    	
    	paint.setColor(color);
		paint.setStyle(Paint.Style.FILL);
    	canvas.drawRect((float)x, (float)y, (float)(x + width), (float)(y + height), paint);			
    }

    public void gradient_fill_rect(int x, int y, int width, int height, int gc_type, int f1, int f2, int gradient) {
    	if ( nodraw)
    		return;

    	setGradient( gradient, f1, f2, (float)x, (float)y, (float)width, (float)height);
		paint.setStyle(Paint.Style.FILL);
    	canvas.drawRect((float)x, (float)y, (float)(x + width), (float)(y + height), paint);			
    	paint.setShader(null);
    }

    public void gradient_fill_rectrounded(int x, int y, int width, int height, int amount, int gc_type, int f1, int f2, int gradient) {
    	if ( nodraw)
    		return;

    	setGradient( gradient, f1, f2, (float)x, (float)y, (float)width, (float)height);
		paint.setStyle(Paint.Style.FILL);
    	canvas.drawRoundRect(new RectF((float)x, (float)y, (float)(x + width), (float)(y + height)), amount, amount, paint);
    	paint.setShader(null);    	
    }
    
    public void arc(int x, int y, int width, int height, int angle1, int angle2, int gc_type, int idx, int highlight) {
    	if ( nodraw)
    		return;

    	if ( gc_type == Glow.eDrawType_LineGray && highlight != 0)
    		gc_type = Glow.eDrawType_Line;

    	int color = getColor(gc_type);

    	paint.setColor(color);
    	paint.setStyle(Paint.Style.STROKE);
    	paint.setStrokeWidth(idx+1);
    	canvas.drawArc(new RectF((float)x, (float)y, (float)(x + width), (float)(y + height)), (float)(360-angle1), (float)(-angle2), false, paint);			

    }

    public void fill_arc(int x, int y, int width, int height, int angle1, int angle2, int gc_type) {
    	if ( nodraw)
    		return;

    	int color = getColor(gc_type);

    	paint.setColor(color);
    	paint.setStyle(Paint.Style.FILL);
    	canvas.drawArc(new RectF((float)x, (float)y, (float)(x + width), (float)(y + height)), (float)(360-angle1), (float)(-angle2), false, paint);			
    }

    public void gradient_fill_arc(int x, int y, int width, int height, int angle1, int angle2, int gc_type, int f1, int f2, int gradient) {
    	if ( nodraw)
    		return;

    	setGradient( gradient, f1, f2, (float)x, (float)y, (float)width, (float)height);
		paint.setStyle(Paint.Style.FILL);
    	canvas.drawArc(new RectF((float)x, (float)y, (float)(x + width), (float)(y + height)), (float)(360-angle1), (float)(-angle2), false, paint);			
    	paint.setShader(null);
    }

    public void line(int x1, int y1, int x2, int y2, int gc_type, int idx, int highlight) {
    	if ( nodraw)
    		return;

    	int color = getColor(gc_type);

		paint.setColor(color);
		paint.setStyle(Paint.Style.STROKE);
		paint.setStrokeWidth(idx+1);
		canvas.drawLine(x1, y1, x2, y2, paint);			
    }

    public void line_dashed(int x1, int y1, int x2, int y2, int gc_type, int idx, int highlight, int line_type) {
    	if ( nodraw)
    		return;

    	int color = getColor(gc_type);

		float[] dash = null;
		switch ( line_type) {
		case Glow.eLineType_Solid: 
			break;
		case Glow.eLineType_Dashed1: 
			dash = new float[] {(float)idx, (float)idx};
			break;
		case Glow.eLineType_Dashed2: 
			dash = new float[] {(float)idx  * 2, (float)idx * 2};
			break;
		case Glow.eLineType_Dashed3: 
			dash = new float[] {(float)idx  * 4, (float)idx * 4};
			break;
		case Glow.eLineType_Dotted: 
			dash = new float[] {(float)idx, (float)idx * 6};
			break;
		case Glow.eLineType_DotDashed1: 
			dash = new float[] {(float)idx * 1, (float)idx * 2, (float)idx  * 4, (float)idx * 2};
			break;
		case Glow.eLineType_DotDashed2: 
			dash = new float[] {(float)idx, (float)idx * 4, (float)idx * 8, (float)idx * 4};
			break;
		}
		
		paint.setColor(color);
		paint.setStyle(Paint.Style.STROKE);
		paint.setStrokeWidth(idx+1);
		if ( dash != null && idx != 0)
			paint.setPathEffect(new DashPathEffect(dash, 0));
		
		canvas.drawLine(x1, y1, x2, y2, paint);			

		if ( dash != null && idx != 0)
			paint.setPathEffect(null);
    }

    public void polyline(GlowPointX[] points, int point_cnt, int gc_type, int idx, int highlight) {
    	if ( nodraw)
    		return;

    	Path path = new Path();
	
    	int color = getColor(gc_type);
    	paint.setColor(color);		
		paint.setStyle(Paint.Style.STROKE);
		paint.setStrokeWidth(idx+1);

    	path.moveTo(points[0].x, points[0].y);
    	for ( int i = 1; i < point_cnt; i++)
    		path.lineTo(points[i].x, points[i].y);
    	canvas.drawPath(path, paint);
    }

    public void fill_polyline(GlowPointX[] points, int point_cnt, int gc_type, int highlight) {
    	if ( nodraw)
    		return;

    	Path path = new Path();
	
    	int color = getColor(gc_type);
    	paint.setColor(color);		
    	paint.setStyle(Paint.Style.FILL);

    	path.moveTo(points[0].x, points[0].y);
    	for ( int i = 1; i < point_cnt; i++)
    		path.lineTo(points[i].x, points[i].y);
    	canvas.drawPath(path, paint);
    }

    public void gradient_fill_polyline(GlowPointX[] points, int point_cnt, int gc_type, int f1, int f2, int gradient) {
    	if ( nodraw)
    		return;

    	Path path = new Path();

    	int x_low = points[0].x;
    	int x_high = points[0].x;
    	int y_low = points[0].y;
    	int y_high = points[0].y;
	
    	int color = getColor(gc_type);
    	paint.setColor(color);		
    	paint.setStyle(Paint.Style.FILL);

    	path.moveTo(points[0].x, points[0].y);
    	for ( int i = 1; i < point_cnt; i++) {
    		path.lineTo(points[i].x, points[i].y);
    		if ( points[i].x > x_high)
    			x_high = points[i].x;
    		if ( points[i].x < x_low)
    			x_low = points[i].x;
    		if ( points[i].y > y_high)
    			y_high = points[i].y;
    		if ( points[i].y < y_low)
    			y_low = points[i].y;
    	}

    	setGradient( gradient, f1, f2, (float)x_low, (float)y_low, (float)(x_high - x_low), (float)(y_high - y_low));
    	canvas.drawPath(path, paint);
    	paint.setShader(null);
    }

    public void text( int x, int y, String text, int gc_type, int color, int idx, int highlight, int line, 
		      int font_idx, double size, int rot) {
    	if ( nodraw)
    		return;

    	int c = getColor(color);

    	if ( gc_type == Glow.eDrawType_TextHelveticaBold && (font_idx & 1) != 0)
    		font_idx++;
    		
    	paint.setTextSize(2.1F * idx + 7);
    	paint.setTypeface(fonts[font_idx]);
    	paint.setColor(c);		
    	paint.setStyle(Paint.Style.FILL);
    	canvas.drawText( text, x, y, paint);

    }

    public int getColor(int gc_type) {
    	GlowColorRgb rgb = GlowColor.rgb_color(gc_type);
    	return Color.rgb((int)(rgb.r * 255), (int)(rgb.g * 255), (int)(rgb.b * 255));
    }
    public  int gradient_rotate(double rotate, int gradient) {
    	return gradient;
    }

    public void setGradient( int gradient, int f1, int f2,
			     			 float x, float y, float w, float h) {
	float gx0 = 0;
	float gy0 = 0;
	float gx1 = 0; 
	float gy1 = 0;
	float gr = 0;
	
	switch ( gradient) {
	case Glow.eGradient_HorizontalUp:
	    gx0 = x;
	    gy0 = y;
	    gx1 = x;
	    gy1 = y + h;
	    break;
	case Glow.eGradient_HorizontalDown:
	    gx0 = x;
	    gy0 = y + h;
	    gx1 = x;
	    gy1 = y;
	    break;
	case Glow.eGradient_HorizontalTube1:
	    gx0 = x;
	    gy0 = y + 0.5F * h;
	    gx1 = x;
	    gy1 = y;
	    break;
	case Glow.eGradient_HorizontalTube2:
	    gx0 = x;
	    gy0 = y + 0.3F * h;
	    gx1 = x;
	    gy1 = y + h;
	    break;
	case Glow.eGradient_VerticalLeft:
	    gx0 = x;
	    gy0 = y;
	    gx1 = x + w;
	    gy1 = y;
	    break;
	case Glow.eGradient_VerticalRight:
	    gx0 = x + w;
	    gy0 = y;
	    gx1 = x;
	    gy1 = y;
	    break;
	case Glow.eGradient_VerticalTube1:
	    gx0 = x + 0.5F * w;
	    gy0 = y;
	    gx1 = x;
	    gy1 = y;
	    break;
	case Glow.eGradient_VerticalTube2:
	    gx0 = x + 0.3F * w;
	    gy0 = y;
	    gx1 = x + w;
	    gy1 = y;
	    break;
	case Glow.eGradient_DiagonalUpperLeft:
	    gx0 = x;
	    gy0 = y;
	    gx1 = x + w;
	    gy1 = y + h;
	    break;
	case Glow.eGradient_DiagonalLowerLeft:
	    gx0 = x;
	    gy0 = y + h;
	    gx1 = x + w;
	    gy1 = y;
	    break;
	case Glow.eGradient_DiagonalUpperRight:
	    gx0 = x + w;
	    gy0 = y;
	    gx1 = x;
	    gy1 = y + h;
	    break;
	case Glow.eGradient_DiagonalLowerRight:
	    gx0 = x + w;
	    gy0 = y + h;
	    gx1 = x;
	    gy1 = y;
	    break;
	case Glow.eGradient_DiagonalUpTube:
	    gx0 = x + 0.5F * w;
	    gy0 = y + 0.5F * h;
	    gx1 = x + w;
	    gy1 = y + h;
	    break;
	case Glow.eGradient_DiagonalDownTube:
	    gx0 = x + 0.5F * w;
	    gy0 = y + 0.5F * h;
	    gx1 = x;
	    gy1 = y + h;
	    break;
	case Glow.eGradient_Globe:
	    gx0 = x + 0.3F * w;
	    gy0 = y + 0.3F * h;
	    gx1 = x + w;
	    gy1 = y + h;
	    gr = (float) Math.sqrt( w*w/4+h*h/4);
	    break;
	case Glow.eGradient_RadialCenter:
	    gx0 = x + 0.5F * w;
	    gy0 = y + 0.5F * h;
	    gx1 = x + w;
	    gy1 = y + h;
	    gr = (float) Math.sqrt( w*w/4F+h*h/4F);
	    break;
	case Glow.eGradient_RadialUpperLeft:
	    gx0 = x;
	    gy0 = y;
	    gx1 = x + w;
	    gy1 = y + h;
	    gr = (float) Math.sqrt( w*w+h*h);
	    break;
	case Glow.eGradient_RadialLowerLeft:
	    gx0 = x;
	    gy0 = y + h;
	    gx1 = x + w;
	    gy1 = y;
	    gr = (float) Math.sqrt( w*w+h*h);
	    break;
	case Glow.eGradient_RadialUpperRight: 
	    gx0 = x + w;
	    gy0 = y;
	    gx1 = x;
	    gy1 = y + h;
	    gr = (float) Math.sqrt( w*w+h*h);
	    break;
	case Glow.eGradient_RadialLowerRight:
	    gx0 = x + w;
	    gy0 = y + h;
	    gx1 = x;
	    gy1 = y;
	    gr = (float) Math.sqrt( w*w+h*h);
	    break;
	default: ;
	}

	switch ( gradient) {
	case Glow.eGradient_HorizontalUp:
	case Glow.eGradient_HorizontalDown:
	case Glow.eGradient_HorizontalTube1:
	case Glow.eGradient_HorizontalTube2:
	case Glow.eGradient_VerticalLeft:
	case Glow.eGradient_VerticalRight:
	case Glow.eGradient_VerticalTube1:
	case Glow.eGradient_VerticalTube2:
	case Glow.eGradient_DiagonalUpperLeft:
	case Glow.eGradient_DiagonalLowerLeft:
	case Glow.eGradient_DiagonalUpperRight:
	case Glow.eGradient_DiagonalLowerRight:
	case Glow.eGradient_DiagonalUpTube:
	case Glow.eGradient_DiagonalDownTube: {
		LinearGradient gp = new LinearGradient( gx0, gy0,
						      gx1, gy1,
						      getColor(f2),getColor(f1), Shader.TileMode.MIRROR);
		paint.setShader(gp);
	    break;
	}
	case Glow.eGradient_Globe:
	case Glow.eGradient_RadialCenter:
	case Glow.eGradient_RadialUpperLeft:
	case Glow.eGradient_RadialLowerLeft:
	case Glow.eGradient_RadialUpperRight: 
	case Glow.eGradient_RadialLowerRight:{
	    RadialGradient gp = new RadialGradient( gx0, gy0, gr, getColor(f2), getColor(f1), Shader.TileMode.CLAMP);
	    paint.setShader(gp);
	    break;
	}
	default: ;
	}
    }	    

    public GlowDimension getTextExtent( String text, int idx, int type, int gc_type) {
    	Rect bounds = new Rect();
    	
    	paint.setTextSize(2.1F * idx + 7);
    	paint.getTextBounds(text, 0, text.length(), bounds);
    	GlowDimension dim = new GlowDimension();
    	dim.width = bounds.width();
    	dim.height = bounds.height();
    	
    	return dim;
    }

    public int set_clip_rectangle( int x1, int y1, int x2, int y2) {
    	canvas.clipRect(x1, y1, x2, y2, Region.Op.REPLACE);
	return 1;
    }

    public void reset_clip_rectangle() {
    	canvas.clipRect(0, 0, canvas.getWidth(), canvas.getHeight(), Region.Op.REPLACE);
    }
}