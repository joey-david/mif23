public class Main {
    public static void main(String[] args) {
        long startTime = System.nanoTime();
        Image im = new Image(1000, 1000);
        for (int h = 0; h < 500; h++) {
            for (int i = 0; i < im.getWidth(); i++) {
                for (int j = 0; j < im.getHeight(); j++) {
                    Pixel temp = im.getPixel(i, j);
                    temp.setR(temp.getR() + 1);
                    temp.setG(temp.getG() + 1);
                    temp.setB(temp.getB() + 1);
                    im.setPixel(i, j, temp);
                    //System.out.print(temp.getR() + "," + temp.getG() + "," + temp.getB() + " ");
                }
                //System.out.println();
            }
        }
        long endTime = System.nanoTime();
        System.out.println("Execution time: " + (endTime - startTime)/1000000 + " ms");
    }
}