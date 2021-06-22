import deadpixel.keystone.*;
Keystone ks;
CornerPinSurface surface;
PGraphics bufor;
public int num = 2000; // dodja kontrolki
Particle particles[]= new Particle[num];

void setup() {

  size(1200, 800, P3D);

  ks = new Keystone(this);
  surface = ks.createCornerPinSurface(400, 300, 20);
  bufor = createGraphics(400, 300, P3D);

  for (int i = 0; i < num; i++) {
    particles[i] = new Particle(i, bufor.height);
  }
}
void draw() {
  
   background(0);

  bufor.beginDraw();
  bufor.noStroke();
  bufor.smooth();
  bufor.fill(255, 80);

  for (int i = 0; i < num; i++) {
    particles[i].update();
    particles[i].render(1);
  }
  bufor.endDraw();
  surface.render(bufor);
}

void keyPressed() {
  switch(key) {
    
  case 'c':
    ks.toggleCalibration(); // enter/leave calibration mode, where surfaces can be warped and moved
    break;
  case 'l':
    ks.load(); // loads the saved layout
    break;
  case 's':
    ks.save(); // saves the layout
    break;
  }
}
