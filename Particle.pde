class Particle {


  PVector velocity;
  PVector position;
  float r;

  Particle (float x, float y ) {
    bufor = createGraphics(400, 300, P3D);

    velocity = new PVector(0, 0);
    position = new PVector(x, y);
  }
  void render (float r) {
   
    bufor.ellipse(position.x, position.y, r, r);
    
  }
  float noiseScale = 700; // mozesz dodac kontorlke 

  void update() {

    float direction = noise((position.x)/noiseScale, position.y/noiseScale)*TWO_PI;

    velocity.x = sin(direction) * 0.45; // mozesz dodac kontorlki
    velocity.y = cos(direction) * 0.3;  // mozesz dodac kontorlki

    position.add(velocity);
    
  }
}
