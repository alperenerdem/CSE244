import java.awt.Graphics;
import java.util.ArrayList;
import javax.swing.*;

public class DrawLines extends JPanel {
    /*Çizeceğim doğrular için x,y koordinatları alacağım datalar, bu dataları fonksiyona göndereceğim */
    private ArrayList<Integer> X = new ArrayList<>();
    private ArrayList<Integer> Y = new ArrayList<>();
    public void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        int height= getHeight();
        int i=0;
        while(i+1<X.size())
        {
            /*Kalın olması için +1 -1'inde de çizgi çekiyorum.
              Net Gözükmesi için zaten 20kat büyük yapmıştım o yüzden +-1 fazla kaydırma yapmıyor */
            g.drawLine(20*X.get(i), height-(20*Y.get(i)), 20*X.get(i+1), height - (20*Y.get(i+1)));
            g.drawLine(20*X.get(i) +1, height-(20*Y.get(i)) +1, 20*X.get(i+1) +1, height - (20*Y.get(i+1)) +1);
            g.drawLine(20*X.get(i) -1, height-(20*Y.get(i)) -1, 20*X.get(i+1) -1, height - (20*Y.get(i+1)) -1);
            i++;
        }
    }
    void DrawLinesWithData(Integer Height, Integer Width, ArrayList<Integer> XList, ArrayList<Integer> YList)
    {
        DrawLines SkyLines= new DrawLines();
        SkyLines.X= XList;
        SkyLines.Y= YList;
        /*DrawLinesWithData fonksiyonunda XveY'lerin listini classımızdaki x ve y'ye atıyorum
        gelen height ve width için pencere boyutlarını belirliyorum */
        JFrame application = new JFrame();
        application.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        application.add(SkyLines);
        application.setTitle("Skylines");
        /*Skyline'nımızı pencereye ekliyoruz,boyutunu ayarlayıp görünür hale getiriyoruz */

        application.setSize(Width*25,Height*30);
        /*Koordinatlar 20 kat büyük yaptığım için
          pencere ondan daha büyük olmalı */

        application.setVisible(true);
    }
}
