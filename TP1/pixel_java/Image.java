public class Image {
    private int width;
    private int height;
    private Pixel[][] tab;

    public Image() {
        this(0, 0);
    }

    public Image(int width, int height) {
        this.width = width;
        this.height = height;
        this.tab = new Pixel[height][width];
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                this.tab[i][j] = new Pixel();
            }
        }
    }

    public int getWidth() {
        return this.width;
    }

    public int getHeight() {
        return this.height;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public Pixel getPixel(int i, int j) {
        return this.tab[i][j];
    }

    public void setPixel(int i, int j, Pixel p) {
        this.tab[i][j] = p;
    }
    
}