#include "Circuit.h"
#include "Gates.h"
#include <fstream>

int main()
{
 Circuit c("circuit.txt");//circuit.txtteki devreyi kur
 c.solve("input.txt");//o devreyi input.txt'teki değerlere göre çöz
}
