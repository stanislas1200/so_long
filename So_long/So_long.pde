// Tiles Image
int dim_x = 4;
int dim_y = 9;
PImage spriteSheetWall;
PImage[] spritesWall = new PImage[dim_x*dim_y];

    String[][] map = {
  {"5","8","8","8","8","5","5","5","8","8","8","8","8","8","8","8","8","8","8","5"},
{"6","X","E","X","X","7","8","9","X","X","X","C","X","W","X","X","P","X","X","0"},
{"6","X","C","X","W","X","W","X","X","2","4","X","X","X","C","2","4","X","W","0"},
{"6","C","C","X","X","X","X","X","C","7","9","X","X","X","2","5","9","X","X","0"},
{"6","X","2","3","4","X","W","X","X","X","X","X","W","X","7","9","C","X","X","0"},
{"6","X","7","8","9","C","W","X","X","C","X","X","X","X","X","X","X","2","3","5"},
{"6","X","C","X","X","X","W","X","X","W","2","4","X","X","X","X","X","7","8","5"},
{"6","X","X","W","X","X","X","X","X","X","7","9","W","X","X","W","X","X","X","0"},
{"6","X","X","X","C","C","C","X","X","X","X","X","C","X","X","W","C","X","X","0"},
{"5","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","5"},
};
 void settings() {
  //fullScreen(P2D, 2);
  size(1500, 850, P2D);
}
 void setup(){
   background(0);
   spriteSheetWall = loadImage("data/texture/Wall.png");
 for (int i=0; i<spritesWall.length; i++) {
    spritesWall[i] = spriteSheetWall.get((i%dim_x)*spriteSheetWall.width/dim_x, (i/dim_x)*spriteSheetWall.height/dim_y, spriteSheetWall.width/dim_x, spriteSheetWall.height/dim_y);
 }


 }
 
 void draw(){
   for (int i = 0; i < 10; i++) {
     for (int j = 0; j < 20; j++) {
       switch (map[i][j])
       {
         case "2":
           image(spritesWall[0], j * 50, i * 50, 50, 50);
           break;
          case "6":
            image(spritesWall[6], j * 50, i *50, 50, 50);
            break;
         case "3":
            image(spritesWall[1], j * 50, i *50, 50, 50);
            break;
          case "4":
            image(spritesWall[2], j * 50, i *50, 50, 50);
            break;
          case "5":
            image(spritesWall[5], j * 50, i *50, 50, 50);
            break;
          case "7":
            image(spritesWall[8], j * 50, i *50, 50, 50);
            break;
            case "8":
            image(spritesWall[9], j * 50, i *50, 50, 50);
            break;
          case "9":
            image(spritesWall[10], j * 50, i *50, 50, 50);
            break;
          case "0":
            image(spritesWall[4], j * 50, i *50, 50, 50);
            break;
          case "W":
            image(spritesWall[19], j * 50, i *50, 50, 50);
            break;
       }
     }
   }
 }
 
