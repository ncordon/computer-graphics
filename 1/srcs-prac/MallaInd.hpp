#include "Objeto3D.hpp"
#include <vector>
#include "tuplasg.hpp"
#include "aux.hpp"

using namespace std;
// clase para mallas indexadas o mallas TVT
class MallaInd : public Objeto3D{
protected:
    vector<Tupla3f> vertices;
    vector<Tupla3i> caras;
public:
    virtual void visualizar( unsigned modo_vis );
};
