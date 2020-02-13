
#include <iostream>
#include "../MMCore/MMCore.h"
#include "../DeviceAdapters/DemoCamera/DemoCamera.h"
#include "../DeviceAdapters/FakeCamera/FakeCamera.h"
#include "../../3rdpartypublic/OpenCV2.4.8/build/include/opencv2/highgui/highgui.hpp"
#include "../../3rdpartypublic/OpenCV2.4.8/build/include/opencv2/imgproc/imgproc.hpp"
#include "../../3rdpartypublic/OpenCV2.4.8/build/include/opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{


     CMMCore core;

     core.setPrimaryLogFile("fichier.txt", false);
     cout << "Fichier log: " << core.getPrimaryLogFile() << "\n";

     core.loadDevice("macamera","DemoCamera" , "DCam");// alternative: "FakeCamera", "FakeCamera");
 
     vector<std::string> devices = core.getLoadedDevices();

     for (int i = 0; i < devices.size(); i++) {
      // Boucle devices

      cout << "Device: " << devices[i] << "\n";
      char* label = (&devices[i][0]);
      vector<std::string> properties = core.getDevicePropertyNames(label);

      for (int j = 0; j < properties.size(); j++) {
       // Boucle propriétés
       char* prop = (&properties[j][0]);
       cout << properties[j] << " = " << core.getProperty(label, prop) << "\n";
      }
     }

     // Réplique de la démonstration de la documentation faite en Java
     core.initializeAllDevices();
     core.setExposure(50);
     // Commande à l'appareil de prendre une image
     core.snapImage();
     long width = core.getImageWidth();
     long height = core.getImageHeight();
     // Retourne un pointeur vers l'image:
     unsigned char * imgP = (unsigned char*) core.getImage();
     cout << "adresse:    " << &imgP <<"\n";
     cout << "w:          " << width << " h:"<< height << "\n";
     cout << "Bytes/pixel:" << core.getBytesPerPixel() << "\n";
     cout << "image:      " << "\n";
     for (int i=0;i<width;i++){
      // L'image est composé une série de bytes:
      cout << (unsigned int)imgP[i] << " ";
     }
 
     // Pour sauvegarder l'image, on utilise opencv
     Mat img = Mat(height, width, CV_8UC1, imgP).clone();
     imwrite("test.jpg", img);

}


