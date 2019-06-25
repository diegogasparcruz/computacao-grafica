#include <iostream>

using namespace std;

//#include <gui.h>
#include <vector>
#include <fstream>
#include <sstream>

//#include <objeto.h>
#include <bus.h>
#include <banco.h>
#include <plaza.h>
#include <pessoa.h>
#include <sol.h>
#include <statue.h>
#include <tree.h>
#include <home.h>
#include <parede.h>

vector<Objeto*> objetos;
int posSelecionado = -1;
int cameraAtual = -1;

vector<Camera*> cameras;

// sombra
bool drawShadow = true;
bool pontual = false;
float k = 0.0;

void salvaArquivo(string arq){

    ofstream abrirArquivo(arq);

    abrirArquivo << objetos.size() << endl;

    for(int i = 0; i < objetos.size(); i++){

        abrirArquivo << objetos[i]->tipo << endl;
        abrirArquivo << objetos[i]->t.x << endl;
        abrirArquivo << objetos[i]->t.y << endl;
        abrirArquivo << objetos[i]->t.z << endl;

        abrirArquivo << objetos[i]->a.x << endl;
        abrirArquivo << objetos[i]->a.y << endl;
        abrirArquivo << objetos[i]->a.z << endl;

        abrirArquivo << objetos[i]->s.x << endl;
        abrirArquivo << objetos[i]->s.y << endl;
        abrirArquivo << objetos[i]->s.z << endl;
    }

}

void carregarArquivo(string arq){

    ifstream arquivo(arq);
    Vetor3D t,a,s;
    string line;
    string tipo;

    getline(arquivo, line);

    int num_objetos = std::stoi(line);

    for(int i = 0; i < num_objetos; i++){

        getline(arquivo, tipo);

        getline(arquivo, line);
        t.x = std::stof(line);
        getline(arquivo, line);
        t.y = std::stof(line);
        getline(arquivo, line);
        t.z = std::stof(line);

        getline(arquivo, line);
        a.x = std::stof(line);
        getline(arquivo, line);
        a.y = std::stof(line);
        getline(arquivo, line);
        a.z = std::stof(line);

        getline(arquivo, line);
        s.x = std::stof(line);
        getline(arquivo, line);
        s.y = std::stof(line);
        getline(arquivo, line);
        s.z = std::stof(line);

        if(std::stoi(tipo) == 1){

            Objeto *banco = new Banco();
            banco->t = t;
            banco->s = s;
            banco->a = a;

            objetos.push_back(banco);

        }

        if(std::stoi(tipo) == 2){

            Objeto *bus = new Bus();
            bus->t = t;
            bus->s = s;
            bus->a = a;

            objetos.push_back(bus);

        }

        if(std::stoi(tipo) == 3){

            Objeto *pessoa = new Pessoa();
            pessoa->t = t;
            pessoa->s = s;
            pessoa->a = a;

            objetos.push_back(pessoa);

        }

        if(std::stoi(tipo) == 4){

            Objeto *plaza = new Plaza();
            plaza->t = t;
            plaza->s = s;
            plaza->a = a;

            objetos.push_back(plaza);

        }

        if(std::stoi(tipo) == 5){

            Objeto *sol = new Sol();
            sol->t = t;
            sol->s = s;
            sol->a = a;

            objetos.push_back(sol);

        }

        if(std::stoi(tipo) == 6){

            Objeto *statue = new Statue();
            statue->t = t;
            statue->s = s;
            statue->a = a;

            objetos.push_back(statue);

        }

        if(std::stoi(tipo) == 7){

            Objeto *tree = new Tree();
            tree->t = t;
            tree->s = s;
            tree->a = a;

            objetos.push_back(tree);

        }

        if(std::stoi(tipo) == 8){

            Objeto *home = new Home();
            home->t = t;
            home->s = s;
            home->a = a;

            objetos.push_back(home);

        }

        if(std::stoi(tipo) == 9){

            Objeto *parede = new Parede();
            parede->t = t;
            parede->s = s;
            parede->a = a;

            objetos.push_back(parede);

        }

    }

}

void desenha() {
    GUI::displayInit();

    //GUI::setLight(1,1,3,5,true,false);
    GUI::setLight(2,-1.5,0.5,-1,true,false);
    GUI::setLight(3,-5,3,5,true,false);

    GUI::drawOrigin(1);

    GUI::setColor(0.50,0.50,0.205);
    GUI::drawFloor();

    //----------------------- SOMBRA ------------------------------------------
    glPushMatrix();
        glTranslated(0.0,k-0.01,0.0);
        GUI::drawFloor(25, 25, 1, 1);
    glPopMatrix();

    float lightPos[4] = {-1+glutGUI::lx,2+glutGUI::ly,1+glutGUI::lz,pontual};
    //GUI::setLight(0,lightPos[0],lightPos[1],lightPos[2],true,false,false,false,pontual);
    GUI::setLight(0,-1,2,1,true,false,false,false,pontual);
    //desenhando os objetos projetados
    glPushMatrix();
        //matriz de projecao para gerar sombra no plano y=k
        GLfloat sombra[4][4];
        //GUI::shadowMatrixYk(sombra,lightPos,k);
        GLfloat plano[4] = {0,1,0,-k};
        GUI::shadowMatrix(sombra,plano,lightPos);
        glMultTransposeMatrixf( (GLfloat*)sombra );

        glDisable(GL_LIGHTING);
        glColor3d(0.0,0.0,0.0);
        if (drawShadow) {
            bool aux = glutGUI::draw_eixos;
            glutGUI::draw_eixos = false;
            for (int i = 0; i < objetos.size(); ++i) {
                glPushMatrix();
                if(objetos[i]->drawShadow){
                    objetos[i]->desenha();
                }

                glPopMatrix();
            }
            glutGUI::draw_eixos = aux;
        }
        glEnable(GL_LIGHTING);
    glPopMatrix();

    glPushMatrix();
        //matriz de projecao para gerar sombra no plano y=k
        sombra[4][4];
        //GUI::shadowMatrixYk(sombra,lightPos,k);
        plano[0] = 1;
        plano[1] = 0;
        plano[2] = 0;
        plano[3] = 2.38;
        GUI::shadowMatrix(sombra,plano,lightPos);
        glMultTransposeMatrixf( (GLfloat*)sombra );

        glDisable(GL_LIGHTING);
        glColor3d(0.0,0.0,0.0);
        if (drawShadow) {
            bool aux = glutGUI::draw_eixos;
            glutGUI::draw_eixos = false;
            for (int i = 0; i < objetos.size(); ++i) {

                glPushMatrix();
                    if(objetos[i]->drawShadow){
                         objetos[i]->desenha();
                    }

                glPopMatrix();
            }
            glutGUI::draw_eixos = aux;
        }
        glEnable(GL_LIGHTING);
    glPopMatrix();

    glPushMatrix();
        //matriz de projecao para gerar sombra no plano y=k
        sombra[4][4];
        //GUI::shadowMatrixYk(sombra,lightPos,k);
        plano[0] = -1;
        plano[1] = 0;
        plano[2] = 0;
        plano[3] = 2.38;
        GUI::shadowMatrix(sombra,plano,lightPos);
        glMultTransposeMatrixf( (GLfloat*)sombra );

        glDisable(GL_LIGHTING);
        glColor3d(0.0,0.0,0.0);
        if (drawShadow) {
            bool aux = glutGUI::draw_eixos;
            glutGUI::draw_eixos = false;
            for (int i = 0; i < objetos.size(); ++i) {

                glPushMatrix();
                    if(objetos[i]->tipo != 9 && objetos[i]->drawShadow){
                         objetos[i]->desenha();
                    }

                glPopMatrix();
            }
            glutGUI::draw_eixos = aux;
        }
        glEnable(GL_LIGHTING);
    glPopMatrix();

    glPushMatrix();
        //matriz de projecao para gerar sombra no plano y=k
        sombra[4][4];
        //GUI::shadowMatrixYk(sombra,lightPos,k);
        plano[0] = 0;
        plano[1] = sqrt(2);
        plano[2] = sqrt(2);
        plano[3] = 2.6;
        GUI::shadowMatrix(sombra,plano,lightPos);
        glMultTransposeMatrixf( (GLfloat*)sombra );

        glDisable(GL_LIGHTING);
        glColor3d(0.0,0.0,0.0);
        if (drawShadow) {
            bool aux = glutGUI::draw_eixos;
            glutGUI::draw_eixos = false;
            for (int i = 0; i < objetos.size(); ++i) {

                glPushMatrix();
                    if(objetos[i]->tipo != 9 && objetos[i]->drawShadow){
                         objetos[i]->desenha();
                    }

                glPopMatrix();
            }
            glutGUI::draw_eixos = aux;
        }
        glEnable(GL_LIGHTING);
    glPopMatrix();

    // --------------------------- SOMBRA ----------------------------------------

    for (int i = 0; i < objetos.size(); ++i) {
        glPushMatrix();
        objetos[i]->desenha();
        glPopMatrix();
    }

    if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
        objetos[posSelecionado]->t.x += glutGUI::dtx;
        objetos[posSelecionado]->t.y += glutGUI::dty;
        objetos[posSelecionado]->t.z += glutGUI::dtz;

        objetos[posSelecionado]->a.x += glutGUI::dax;
        objetos[posSelecionado]->a.y += glutGUI::day;
        objetos[posSelecionado]->a.z += glutGUI::daz;

        objetos[posSelecionado]->s.x += glutGUI::dsx;
        objetos[posSelecionado]->s.y += glutGUI::dsy;
        objetos[posSelecionado]->s.z += glutGUI::dsz;
    }

    GUI::displayEnd();
}

bool incluirObjeto = false;

void teclado(unsigned char key, int x, int y) {
    //if (!incluirObjeto) {
    GUI::keyInit(key,x,y);
    //}

    switch (key) {
    case 't':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        break;
    case 'l':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;

    case 'n':
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->selecionado = false;
        }
        posSelecionado++;
        posSelecionado = posSelecionado%objetos.size();
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->selecionado = true;
        }
        break;
    case 'b':
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->selecionado = false;
        }
        posSelecionado--;
        if (posSelecionado < 0) {
            posSelecionado = objetos.size()-1;
        }
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->selecionado = true;
        }
        break;


    case 'O':
        incluirObjeto = !incluirObjeto;
        break;

    case 'a':
        if(incluirObjeto){
            objetos.push_back( new Bus() );
        }
        break;

    case 'e':
        if(incluirObjeto){
            objetos.push_back( new Banco() );
        }
        break;

    case 'w':
        if(incluirObjeto){
            objetos.push_back( new Plaza() );
        }
        break;

    case 'd':
        if(incluirObjeto){
            objetos.push_back( new Pessoa() );
        }
        break;

    case 's':
        if(incluirObjeto){
            objetos.push_back( new Sol() );
        }
        break;

    case 'f':
        if(incluirObjeto){
            objetos.push_back( new Statue() );
        }
        break;

    case 'F':
        if(incluirObjeto){
            objetos.push_back( new Tree() );
        }
        break;

    case 'h':
        if(incluirObjeto){
            objetos.push_back( new Home() );
        }
        break;

    case 'p':
        if(incluirObjeto){
            objetos.push_back( new Parede() );
        }
        break;

    case '?':
        drawShadow = true;
        break;

    case '/':
        drawShadow = false;
        break;

    case 'g':

        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->eixo = !objetos[posSelecionado]->eixo;
            cout << objetos[posSelecionado]->eixo << endl;
        }

        break;

    case '+':

        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->drawShadow = !objetos[posSelecionado]->drawShadow;
            cout << objetos[posSelecionado]->drawShadow << endl;
        }

        break;

    case 'D':

        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos.erase(objetos.begin()+posSelecionado,objetos.begin()+posSelecionado+1);
            posSelecionado = -1;
        }

        break;

    case 'Q':

        objetos.pop_back();

        break;

    case 'S':

        salvaArquivo("arq.txt");

        break;

    case 'R':

        carregarArquivo("arq.txt");

        break;

    case 'c':
        cameraAtual++;
        cameraAtual = cameraAtual%cameras.size();

        glutGUI::cam = new CameraDistante(cameras[cameraAtual]->e,cameras[cameraAtual]->c,cameras[cameraAtual]->u);
    break;

    case '5':

        glutGUI::projecao++;
        glutGUI::projecao = glutGUI::projecao%3;

    break;

    case '{':

        pontual = !pontual;

    break;

    default:
        break;
    }
}

int main()
{
    cout << "Hello World!" << endl;

    cameras.push_back(new CameraDistante(6,6,6,0,0,0,0,1,0));
    cameras.push_back(new CameraDistante(6,2,6,0,0,0,0,1,0));
    cameras.push_back(new CameraDistante(1,2,6,0,0,0,0,1,0));
    cameras.push_back(new CameraDistante(0,10,0,0,0,0,1,0,0));
    cameras.push_back(new CameraDistante(10,1,0,0,0,0,0,1,0));
    cameras.push_back(new CameraDistante());

    GUI gui = GUI(800,600,desenha,teclado);
}

