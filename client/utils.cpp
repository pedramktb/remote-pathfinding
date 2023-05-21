#include <string>

class Utils{
public:
    static void handle(std::string input, std::string response){
        try {
            //Process String
            int xy[4];
            std::string s = input;
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
        }
        catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        }
    }
};