#include <iostream>

using namespace std;

#include <gui.h>
#include <vector>
#include <pista.h>
#include <fstream>
#include <sstream>

//-------------------picking------------------
vector<Vetor3D> pontosControle;
Pista *pista = new Pista();
Camera *camera = new CameraDistante();
Camera *cameraPrincipal = new CameraDistante();
bool status = true;
float discreta = .034;

int pontoSelecionado = 0; //names = [1,n] //n = pontosControle.size()
//bool transPontos = glutGUI::trans_obj; //= true;

//salvar arquivo
void salvaArquivo(string arq){

    ofstream abrirArquivo(arq);
    abrirArquivo.clear();
    abrirArquivo << pontosControle.size() << endl;

    for(int i = 0; i < pontosControle.size(); i++){

        abrirArquivo << pontosControle[i].x << endl;
        abrirArquivo << pontosControle[i].y << endl;
        abrirArquivo << pontosControle[i].z << endl;
    }

}

void carregarArquivo(string arq){

    ifstream arquivo(arq);
    pontosControle.clear();

    Vetor3D t;
    string line;

    getline(arquivo, line);

    int num_points = std::stoi(line);

    for(int i = 0; i < num_points; i++){

        getline(arquivo, line);
        t.x = std::stof(line);
        getline(arquivo, line);
        t.y = std::stof(line);
        getline(arquivo, line);
        t.z = std::stof(line);

        pontosControle.push_back(t);

    }

}

void desenhaPontosDeControle()
{
    //desenhando pontos de controle
    for (int i=0; i<pontosControle.size(); i++) {
        //definindo cor da selecao
        if (i == pontoSelecionado-1) {
            GUI::setColor(1,1,1,1,true);
        } else {
            GUI::setColor(0,0,1,1,true);
        }
        //desenhando (definindo nomes para o picking)
        Vetor3D p = pontosControle[i];
        glPushName(i+1); //não se deve definir name = 0!
            GUI::drawSphere(p.x,p.y,p.z,0.2);
        glPopName();
    }
}

//picking
int picking( GLint cursorX, GLint cursorY, int w, int h ) {
    int BUFSIZE = 512;
    GLuint selectBuf[512];

    GUI::pickingInit(cursorX,cursorY,w,h,selectBuf,BUFSIZE);

//de acordo com a implementacao original da funcao display
    //lembrar de nao inicializar a matriz de projecao, para nao ignorar a gluPickMatrix
    GUI::displayInit();
    //só precisa desenhar o que for selecionavel
    desenhaPontosDeControle();
//fim-de acordo com a implementacao original da funcao display

    //retornando o name do objeto (ponto de controle) mais proximo da camera (z minimo! *[matrizes de normalizacao da projecao])
    return GUI::pickingClosestName(selectBuf,BUFSIZE);
}
//-------------------picking------------------

//-------------------viewPorts------------------
bool viewports = false;
bool scissored = false;

void cenario();

//visao de duas cameras (duas viewports), viewport auxiliar sobrepondo a principal
void viewPorts() {
    float width = glutGUI::width;
    float height = glutGUI::height;

    //viewport principal
    glViewport(0, 0, width, height);
        glLoadIdentity();
        gluLookAt(glutGUI::cam->e.x,glutGUI::cam->e.y,glutGUI::cam->e.z, glutGUI::cam->c.x,glutGUI::cam->c.y,glutGUI::cam->c.z, glutGUI::cam->u.x,glutGUI::cam->u.y,glutGUI::cam->u.z);
            cenario();

    //viewport auxiliar sobrepondo a principal
    if (!scissored) {
        //misturando com a principal
        glViewport(0, 3*height/4, width/4, height/4);
    } else {
        //recortando/substituindo o pedaço
        GUI::glScissoredViewport(0, 3*height/4, width/4, height/4);
    }
        glLoadIdentity();
        if(status)
            gluLookAt(camera->e.x,camera->e.y,camera->e.z,camera->c.x,camera->c.y,camera->c.z,camera->u.x,camera->u.y,camera->u.z);
        else
            gluLookAt(cameraPrincipal->e.x,cameraPrincipal->e.y,cameraPrincipal->e.z,cameraPrincipal->c.x,cameraPrincipal->c.y,cameraPrincipal->c.z,cameraPrincipal->u.x,cameraPrincipal->u.y,cameraPrincipal->u.z);
        cenario();
}
//-------------------viewPorts------------------

void cenario() {
    //GUI::setLight(1,1,3,5,true,false);
    //GUI::setLight(2,-1.5,0.5,-1,true,false);
    GUI::setLight(3,-5,3,5,true,false);

    GUI::drawOrigin(0.5);

    //GUI::setColor(1,0,0);
    //GUI::drawFloor();
    GUI::setColor(0,0,0);
    Desenha::drawGrid( 5, 0, 1, 1 );

    desenhaPontosDeControle();
    pista->desenha(pontosControle, discreta);
    pista->desenhaBoneco(pontosControle, camera);
    pista->andar();
}

void desenha() {
    GUI::displayInit();

    if (!viewports) {
        cenario();
    } else {
        viewPorts();
    }

    //transladando ponto selecionado atraves do picking
    //if (pontoSelecionado > 0 and pontoSelecionado <= objetos.size()) {
    if (pontoSelecionado!=0) {
        pontosControle[pontoSelecionado-1].x += glutGUI::dtx;
        pontosControle[pontoSelecionado-1].y += glutGUI::dty;
        pontosControle[pontoSelecionado-1].z += glutGUI::dtz;
    }

    GUI::displayEnd();
}

void teclado(unsigned char key, int x, int y) {
    GUI::keyInit(key,x,y);
    Vetor3D novo;
    int ax;
    switch (key) {
    case 't':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        //transPontos = glutGUI::trans_obj;
        break;
    case 'l':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;

    case 'v':
        viewports = !viewports;
        break;
    case 's':
        scissored = !scissored;
        break;

    case 'd':

       pista->mudarMatriz();

        break;

    case 'g':

        if(status){
            cameraPrincipal = glutGUI::cam;
            glutGUI::cam = camera;
        }else{
            glutGUI::cam = cameraPrincipal;

        }
        status = !status;

      break;
    case 'h':
        discreta += .0002;
        break;

    case 'H':
         if(discreta > 0.004) discreta -= .0002;
        break;
    case 'P':
        ax = pontosControle.size();
        novo = pontosControle[ax-1] + pontosControle[ax-2];
        novo.x /= 2;
        novo.y /= 2;
        novo.z /= 2;
        pontosControle.push_back(novo);
        break;

    case 'p':
        if(pontosControle.size() > 4) pontosControle.pop_back();
        break;
    case '>':
        pista->acelerar();
        break;

    case '<':
        pista->re();
        break;

    case '.':
        pista->para();
        break;

    case 'S':
        salvaArquivo("arq.txt");
        break;

    case 'K':
       carregarArquivo("arq.txt");
        break;

    default:
        break;
    }
}

void mouse(int button, int state, int x, int y) {
    GUI::mouseButtonInit(button,state,x,y);

    // if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        // when the button is pressed
        if (state == GLUT_DOWN) {
            //picking
            int pick = picking( x, y, 5, 5 );
            if (pick != 0) {
                pontoSelecionado = pick;
                glutGUI::lbpressed = false;
            }
        }
    }
}

int main()
{
    cout << "Hello World!" << endl;

    pontosControle.push_back( Vetor3D(-2, -2, 0) );
    pontosControle.push_back( Vetor3D(2, -2, 0) );
    pontosControle.push_back( Vetor3D(2, 2, 0) );
    pontosControle.push_back( Vetor3D(-2, 2, 0) );


    GUI gui = GUI(800,600,desenha,teclado,mouse);
}














