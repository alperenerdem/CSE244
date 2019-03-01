import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

class Files {
    void openFile(String Filename, SkylineData Sky) {
        Scanner reader;
        try {
            reader =new Scanner(new File(Filename));
            while(reader.hasNext())
            {
                    /*Okuduklarımı atmak istediğim data 2 boyutlu bir array list olduğu için
                     * burada yeni bir tek boyutlu ArrayList'e her binanın bilgilerini alıp,
                     * data'ya teker teker ekliyorum.*/
                    ArrayList<Integer> Data= new ArrayList<>();
                    Data.clear();
                    Data.add(reader.nextInt());
                    Data.add(reader.nextInt());
                    Data.add(reader.nextInt());
                    Sky.AddBuildingToSkyData(Data);

            }
        } catch (FileNotFoundException e) {
            System.out.println("File Not Found");
            System.exit(1);
        }

    }

}
