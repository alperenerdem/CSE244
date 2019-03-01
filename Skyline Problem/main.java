public class main {
    public static void main(String[] args) {
        /*Yeni bir SkylineData objesi oluşturuyorum, ve data.txt'teki binaları objeye ekliyorum
         * Sonra objedeki binaları location'larına göre sıralıyorum,Köşelerini bulup köşelerini ekrana basıyorum
          * Daha sonra Ekrana çizdirmek için bir DrawLines objesi oluşturuyorum,
          * İlk oluşturduğum SkylineData objesindeki yükseklik,genişlik ve köşelerin koordinatlarını
           * DrawLinesWithData fonksiyonuna atıp ekrana çizgileri çizdiriyorum.*/
        SkylineData MySkylines = new SkylineData();
        Files file1=new Files();
        file1.openFile("data.txt",MySkylines);
        MySkylines.SortSkyData();
        MySkylines.FindSkyCorners();
        MySkylines.printCorners();
        DrawLines SkylineDraw = new DrawLines();
        SkylineDraw.DrawLinesWithData(MySkylines.getMaxHeight(),MySkylines.getMaxWidth(), MySkylines.getXofPoint(),MySkylines.getYofPoint());
    }
}
