static final float ANGLE = 0;
static final float ANGLE_STEP = 0.2;

static final int MINSIZE = 40;
static final int MAXSIZE = 51;
static final int MAX_STEP = 2;

static final String[] FONT_LIST = PFont.list();

void setup(){
    size(50,50);
    background(0);
    noStroke(); 
    //fill(255);
    textSize(50);
    textAlign(CENTER, CENTER);
}


String getFilename(int nombre, int nbDigit){
    
  String result = str(nombre);
  
  for(int i = result.length(); i < nbDigit; i++){
      result = "0"+result;
    
  }

  
  return result;
  
}


void draw(){

  int w = 0;
  for (int fonti = 0; fonti < FONT_LIST.length; fonti++){ 
    String font = FONT_LIST[fonti];

        for(int textSize = MINSIZE; textSize < MAXSIZE; textSize += MAX_STEP){
          PFont Font1 = createFont(font, textSize);
           textFont(Font1);
           for(int i = 33; i < 127; i++){
              background(0);
              pushMatrix();
              translate(width/2,height/2/*-height/4*/);
              text(str(char(i)),0,0);
              popMatrix();
              save(getFilename(i, 3)+"/"/*+font+str(angle)*/+str(w)+/*str(textSize)+*/".bmp");
            }
            w++;
          }
    }
    noLoop();
}
