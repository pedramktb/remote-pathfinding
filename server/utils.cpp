#include <string>
#include "pathfinding.cpp"

class Utils{
public:
    static std::string handle(std::string message){
        try {
            //Process String
            int xy[4];
            std::string s = message;
            std::string delimiter = ",";
            size_t pos = 0;
            for(int i=0;i<4;i++){
                if((pos = s.find(delimiter)) != std::string::npos){
                    xy[i]=std::stoi(s.substr(0,pos));
                    s.erase(0, pos + delimiter.length());
                }
                else {
                    xy[i]=std::stoi(s);
                }
            }
            std::cout << xy[0] << ' ' << xy[1] << ' ' << xy[2]  << ' ' << xy[3] << std::endl; //Debug

            //Solve Problem
            Pathfinding pf = Pathfinding("map.npy", 50, 50);
            return pf.find(xy);
        }
        catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        }
    }
};