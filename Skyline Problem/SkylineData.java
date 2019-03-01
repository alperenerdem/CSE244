import java.util.ArrayList;
import java.util.Comparator;

class SkylineData {
    private ArrayList<ArrayList<Integer>> SkyData = new ArrayList<>();
    private ArrayList<Integer> XofPoint = new ArrayList<>();
    private ArrayList<Integer> YofPoint = new ArrayList<>();
    private Integer MaxWidth=0;// Skylineların en sağ noktası
    private Integer MaxHeight=0;// Skylinelardaki en yüksek noktanın yüksekliği

    Integer getMaxHeight()
    {
        return MaxHeight;
    }
    Integer getMaxWidth()
    {
        return MaxWidth;
    }
    ArrayList<Integer> getXofPoint()
    {
        return XofPoint;
    }
    ArrayList<Integer> getYofPoint()
    {
        return YofPoint;
    }

    void AddBuildingToSkyData(ArrayList<Integer> data)
    {
        SkyData.add(data);
    }
    private void SetXandYofPoint(Integer i, Integer j)
        /*Koordinatları ayrı ayrı atmamak için tek bir fonksiyonda 2 dataya beraber ekliyorum */
    {
        XofPoint.add(i);
        YofPoint.add(j);
    }
    private Integer GetX(Integer i)
    {
        return XofPoint.get(i);
    }
    private Integer GetY(Integer i)
    {
        return YofPoint.get(i);
    }
    void SortSkyData()
        /*2d ArrayListi 2.sütunundaki(location) elemanlara göre sıralıyorum
         * Aslında collections.sort(Skydata,comparator..) kullanmıştım fakat kullandığım IDE böyle yapmamı önerdi
         * Öğrenilmesi daha kolay ve daha kısa olduğu için bu şekilde kullandım*/
    {
        SkyData.sort(Comparator.comparing(o -> o.get(2)));
    }

    void FindSkyCorners()
    {
        int x = 0;
        double position;
        int maxHeight=0;
        int y=0;
        int tempY=-1;
        int tempHeight = 0;
        int tempmaxHeight;
        /*son dakika güncellemesi:
          tempY ve tempmaxHeight(2. en yüksek konum) son dakika ödevde bulduğum 2-3 bugu düzeltmek için koyduğum 2 değişken
          Eğer binalar arasında tek birim fark varsa aşağıda kalan yüksekliği daima yok sayıyordu,
          bunun için positionu double olarak değiştirip positionu içeren binaların arasında yükseklik kıyasladım
          örnek: 5.5 positionunu 1 1 5 şekilde datası olan bina içeriyor.

          Aradaki tek birim fark için 2.yüksekliği(eğer yoksa sıfır) olacak şekilde aldım ve
          kodumdaki yüksekliğin azaldığı duruma 2 adet 2.yüksekliği alan koordinat ekledim ve hatayı çözdüm.
          */
        while (y < SkyData.size()) {
            if (SkyData.get(y).get(2) + SkyData.get(y).get(0)>MaxWidth) {
                MaxWidth=SkyData.get(y).get(2) + SkyData.get(y).get(0);
            }
            y++;
        }

        position = SkyData.get(x).get(2) + 0.5 ;/*Sıralı olduğu için ilk position ilk elemanınkine eşit */

        /*ilk pozisyon son elemanın pozisyon+genişliğinden küçük-eşit olana kadar
         *
         * Her pozisyondaki en yüksek binayı buluyorum(tüm binalara bakarak)
         *ve pozisyonda ilerlerken, Eğer yükseklik değişirse köşeye denk geldiğini biliyorum
         * (Yükseklik değişmesini tempHeight değişkeniyle kontrol ediyorum)
         * Bulduğum köşeyi Koordinat Tutan XofPoint ve YofPoint Arraylistime ekliyorum,
         *
         *  Ve bunları kontrol ederken çizerken yardımcı olması için,
         * en yüksek Binanın yüksekliğinide classtaki MaxHeight değişkenime alıyorum*/
        while (position <= MaxWidth) {
            y = 0;
            maxHeight = -1;
            tempmaxHeight=-1;
            while (y < SkyData.size()) {
                if ((position <= (SkyData.get(y).get(2) + SkyData.get(y).get(0))) && position >= SkyData.get(y).get(2)) {
                    if (SkyData.get(y).get(1) > maxHeight) {
                        tempmaxHeight=maxHeight;
                        tempY = y;
                        maxHeight = SkyData.get(y).get(1);
                        if(maxHeight>MaxHeight){
                            MaxHeight=maxHeight;
                        }
                    }
                }
                y++;
            }
            if(maxHeight==-1) {
                maxHeight = 0;
            }
            if (tempHeight < maxHeight) {

                SetXandYofPoint((int) (position- 0.5), tempHeight);
                SetXandYofPoint((int) (position- 0.5), maxHeight);
            }
            if (tempHeight > maxHeight) {
                if(tempmaxHeight!=-1&&(position <= (SkyData.get(tempY).get(2) + SkyData.get(tempY).get(0))) && position >= SkyData.get(tempY).get(2)){
                    SetXandYofPoint((int) (position - 1.5), tempHeight);
                    SetXandYofPoint((int) (position - 1.5), tempmaxHeight);
                    SetXandYofPoint((int) (position- 0.5) , tempmaxHeight);
                    SetXandYofPoint((int) (position- 0.5) , maxHeight);
                }
                else {
                    SetXandYofPoint((int) (position - 0.5), tempHeight);
                    SetXandYofPoint((int) (position - 0.5), maxHeight);
                }
            }
            tempHeight = maxHeight;
            position++;
        }
        SetXandYofPoint((int) (position - 0.5), maxHeight);
        SetXandYofPoint((int) (position - 0.5), 0);
    }
    void printCorners()
    {
        int i;
        for (i=0; i<XofPoint.size(); i++){
            System.out.printf("(%d, %d)",GetX(i),GetY(i));
            if(i+1!=XofPoint.size()) {//sonda virgül olmaması için
                System.out.print(", ");
            }
        }
        System.out.println();
    }
}
