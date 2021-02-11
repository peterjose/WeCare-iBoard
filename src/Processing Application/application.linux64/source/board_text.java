import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import controlP5.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class board_text extends PApplet {

// text translate


ControlP5 cp5;

String textValue = "";
String msg = "";
volatile boolean newmsg;
int resetCounter;

// virtual board
Cube c01;
Cube c02;
Cube c03;
Cube c04;
Cube c05;
Cube c06;
Cube c07;
Cube c08;
Cube c09;
Cube c10;
Cube c11;
Cube c12;
Cube c13;
Cube c14;
Cube c15;
Cube c16;

int d = 80;
int l = 320;
int x1 = 290;
int y1 = 20;
int r = 70; // cube dimension
int shift = d/2;

int rectColor, baseColor; 
int rectColor01, rectColor02, 
      rectColor03, rectColor04,
      rectColor05, rectColor06,
      rectColor07, rectColor08, rectColor09;
int rectColor10, rectColor11, rectColor12, 
      rectColor13, rectColor14,
      rectColor15, rectColor16;
      
int rectHighlight, rectPress, rectActive;
int smileC, sadC, heartC, boxC;

int currentColor;
boolean rectOver = false;
boolean circleOver = false;

public void setup() {

  resetCounter = second() + 10;  
  
  
  // text translate
  newmsg = false;
  
  PFont font = createFont("arial",12);
  
  cp5 = new ControlP5(this);
  
  cp5.addTextfield("input")
     .setPosition(20,100)
     .setSize(200,40)
     .setFont(font)
     .setFocus(true)
     .setColor(color(255,0,0))
     ;
       
  cp5.addBang("send")
     .setPosition(140,150)
     .setSize(80,40)
     .setFont(font)
     .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
     ;
     
  textFont(font); 
  
  // virtual board
  background(0);
  
  smileC = color(0, 255, 0);
  sadC = color(0, 0, 255);
  heartC = color(255, 0, 0);
  
  baseColor = color(255);
  rectColor = baseColor;
  resetBoard();
  rectHighlight = color(155,155,155,100);
  rectPress = color(255,0,0);
  
  initBoard();
}

public void draw() {
  background(0);

  // text translate
  fill(255);
  text("Send a smile, sad, or heart message!", 20,80);
  msgTranslate(msg);
  text(msg, 20,220);
  rectMode(CENTER);
  
  // reset after 10 sec
  if (resetCounter != 0 && resetCounter <= second()) {
    resetBoard();
    resetCounter = 0;
    //println(resetCounter);
  }
  
  // virtual board
  createBoard();
}


//////  Functions  //////

public void controlEvent(ControlEvent theEvent) { 
  if(theEvent.isController()) { 
    if(theEvent.getController().getName()=="send") {
      msg = cp5.get(Textfield.class,"input").getText();
      newmsg = true;
    }  
  }
  
  // TODO: add a reset button
}


// hard code the message here
// it coulde be anything
// use rectColorXX = color(R,G,B)
// XX -> number of th cube that should be activated

public void msgTranslate(String txt) {
  if (newmsg) {
    resetCounter = second() + 10;
    if (txt.equals("smile")) {
      rectColor02 = smileC;
      rectColor03 = smileC;
      rectColor09 = smileC;
      rectColor12 = smileC;
      rectColor14 = smileC;
      rectColor15 = smileC;
    } 
    else if (txt.equals("sad")) {
      rectColor02 = sadC;
      rectColor03 = sadC;
      rectColor10 = sadC;
      rectColor11 = sadC;
      rectColor13 = sadC;
      rectColor16 = sadC;
    } 
    else if (txt.equals("heart")) {
      rectColor05 = heartC;
      rectColor07 = heartC;
      rectColor09 = heartC;
      rectColor10 = heartC;
      rectColor11 = heartC;
      rectColor14 = heartC;
    }
  } 

  newmsg = false;
}

/// create the board

public void initBoard () {
  // 1st row
  c01 = new Cube(x1+shift,y1+shift,r);
  c02 = new Cube(x1+d+shift,y1+shift,r);
  c03 = new Cube(x1+2*d+shift,y1+shift,r);
  c04 = new Cube(x1+3*d+shift,y1+shift,r);
  // 2nd row
  c05 = new Cube(x1+shift,y1+d+shift,r);
  c06 = new Cube(x1+d+shift,y1+d+shift,r);
  c07 = new Cube(x1+2*d+shift,y1+d+shift,r);
  c08 = new Cube(x1+3*d+shift,y1+d+shift,r);
  // 3rd row
  c09 = new Cube(x1+shift,y1+2*d+shift,r);
  c10 = new Cube(x1+d+shift,y1+2*d+shift,r);
  c11 = new Cube(x1+2*d+shift,y1+2*d+shift,r);
  c12 = new Cube(x1+3*d+shift,y1+2*d+shift,r);
  // 4th row
  c13 = new Cube(x1+shift,y1+3*d+shift,r);
  c14 = new Cube(x1+d+shift,y1+3*d+shift,r);
  c15 = new Cube(x1+2*d+shift,y1+3*d+shift,r);
  c16 = new Cube(x1+3*d+shift,y1+3*d+shift,r);
}

public void createBoard() {
  // Grid
  // horizontal lines
  stroke(255);
  line(x1,y1,x1+l,y1);
  line(x1,y1+d,x1+l,y1+d);
  line(x1,y1+2*d,x1+l,y1+2*d);
  line(x1,y1+3*d,x1+l,y1+3*d);
  line(x1,y1+4*d,x1+l,y1+4*d);
  
  // vertical lines
  stroke(255);
  line(x1,y1,x1,y1+l);
  line(x1+d,y1,x1+d,y1+l);
  line(x1+2*d,y1,x1+2*d,y1+l);
  line(x1+3*d,y1,x1+3*d,y1+l);
  line(x1+4*d,y1,x1+4*d,y1+l);
  
  c01.display(rectColor01);
  c02.display(rectColor02);
  c03.display(rectColor03);
  c04.display(rectColor04);
  c05.display(rectColor05);
  c06.display(rectColor06);
  c07.display(rectColor07);
  c08.display(rectColor08);
  c09.display(rectColor09);
  c10.display(rectColor10);
  c11.display(rectColor11);
  c12.display(rectColor12);
  c13.display(rectColor13);
  c14.display(rectColor14);
  c15.display(rectColor15);
  c16.display(rectColor16);
  
  c01.update(mouseX,mouseY);
  c02.update(mouseX,mouseY);
  c03.update(mouseX,mouseY);
  c04.update(mouseX,mouseY);
  c05.update(mouseX,mouseY);
  c06.update(mouseX,mouseY);
  c07.update(mouseX,mouseY);
  c08.update(mouseX,mouseY);
  c09.update(mouseX,mouseY);
  c10.update(mouseX,mouseY);
  c11.update(mouseX,mouseY);
  c12.update(mouseX,mouseY);
  c13.update(mouseX,mouseY);
  c14.update(mouseX,mouseY);
  c15.update(mouseX,mouseY);
  c16.update(mouseX,mouseY);
}


// reset the board - change color of all cubes to baseColor
public void resetBoard() {
  rectColor01 = baseColor; rectColor02 = baseColor;
  rectColor03 = baseColor; rectColor04 = baseColor;
  rectColor05 = baseColor; rectColor06 = baseColor;
  rectColor07 = baseColor; rectColor08 = baseColor; 
  rectColor09 = baseColor; rectColor10 = baseColor;
  rectColor11 = baseColor; rectColor12 = baseColor; 
  rectColor13 = baseColor; rectColor14 = baseColor;
  rectColor15 = baseColor; rectColor16 = baseColor;
}

class Cube {
  int c;
  float xpos;
  float ypos;
  float w;
  float stat;
  
  // defined constructor with arguments
  Cube(float tempX1, float tempY1, float tempW) { 
    xpos = tempX1;
    ypos = tempY1;
    w = tempW;
  }
  
  public void display(int c) {
    stroke(100);
    fill(c);
    rectMode(CENTER);
    rect(xpos,ypos,w,w);
  }
  
  public void update(int x, int y) {
    if ( overRect(xpos, ypos, w, w) ) {
      rectOver = true; hover();
    } else {
      rectOver = false;
    }
  }
  
  public boolean overRect(float x, float y, float width, float height)  {
    if (mouseX >= x-width/2 && mouseX <= x+width/2 && 
        mouseY >= y-width/2 && mouseY <= y+height/2) {
      return true;
    } else {
      return false;
    }
  }
  
  public int press(float x, float y) {
    if (overRect(x,y,w,w)) {
      return rectPress;
    } else return baseColor;
  }
  
  public void hover() {
      fill(rectHighlight);
      rectMode(CENTER);
      rect(xpos,ypos,w,w);
  }
  
  public void activate() {
      fill(rectActive);
      rectMode(CENTER);
      rect(xpos,ypos,w,w);
  }
}
  public void settings() {  size(700,400); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "board_text" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
