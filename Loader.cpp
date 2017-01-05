#include "Loader.h"

void Loader::process(std::string input)
{
    std::string identifier; //used to identify where the input should go


    points temppoint;
    normal tempnormal;
    coordinate tempcoord;
    face tempface; 


    std::string read;       // used to read the curent line

    int readNum; // this is the number that has just been read in
    char skip; // a char to skip thr /
    int i;
    int count= 1;

    //other things to take into account
    //****************************************
    std::string l_name;
    bool firstRun = true;
    std::string parse;
    //**************************************


    m_inFile.open(input);



    //creation of the reading loop

    m_inFile >> identifier;

    do {
         // check to see what the opening is

        if (identifier =="#")
        {
            getline(m_inFile,read); // use this to read the whole line

        }
        else if(identifier == "v")
        {
            m_inFile >> temppoint.x >> temppoint.y >> temppoint.z;
            inputPoints(temppoint);
        }
        else if(identifier == "vn")
        {
            m_inFile >> tempnormal.vn[0] >> tempnormal.vn[1] >> tempnormal.vn[2];
            inputNormals(tempnormal);
        }
        else if (identifier == "vt")
        {
            m_inFile >> tempcoord.vt[0] >> tempcoord.vt[1] >> tempcoord.vt[2];
            inputCoordinates(tempcoord);
        }
        else if(identifier == "f")
        {


            for( i =0; i < 3; i++)
            {
                count++;


                m_inFile >> readNum;
                if(readNum == 0)
                    break;
                readNum--;
                tempface.p[i].x = m_points[readNum].x;
                tempface.p[i].y = m_points[readNum].y;
                tempface.p[i].z = m_points[readNum].z;


                m_inFile >> skip >> readNum;
                readNum--;
                tempface.coord[i].vt[0] = m_coords[readNum].vt[0];
                tempface.coord[i].vt[1] = m_coords[readNum].vt[1];
                tempface.coord[i].vt[2] = m_coords[readNum].vt[2];


                m_inFile >> skip >> readNum;
                readNum--;
                tempface.norm[i].vn[0] = m_normals[readNum].vn[0];
                tempface.norm[i].vn[1] = m_normals[readNum].vn[1];
                tempface.norm[i].vn[2] = m_normals[readNum].vn[2];



            }

            tempface.name = l_name; // this gives the mtl name to the face so it can be compared and applied later

            createFaces(tempface);

        }
        else if(identifier =="mtllib")
        {
            m_inFile >> identifier;
            identifier = "test/" + identifier;
            processMTL(identifier);
        }

        else if(identifier == "usemtl")
        {
        // chnages the mtl that is being applied
            m_inFile >> read;

            l_name = read; // so the face can have 

        }
        else 
        {
            getline(m_inFile,read);
            std::cout << "Not Processed From Loader" << identifier << " " << read <<std::endl;
        }

        m_inFile >> identifier;

    } while (!m_inFile.eof());
    //m_inFile.close();
    //m_inFile.~basic_ifstream();
}



void Loader::draw()
{
    int i;
    int j;
    int k;

    std::string currentTex;

    glEnable(GL_TEXTURE_2D);
    //glDisable(GL_TEXTURE_2D);
    //glBegin(GL_TRIANGLES);

    for (i=0; i < m_faces.size();i++)
    {
        //bind a certain image 
        for (k=0; k<m_mtl.size();k++)
        {
            if (m_mtl[k].compare(m_faces[i].name) == true)
            {
                //these next two lines do the same thing
                //m_mtl[k].draw();
                glBindTexture(GL_TEXTURE_2D,m_mtl[k].getGLID());
                //break; // break out of the loop
            }

        }

        glBegin(GL_TRIANGLES);

        for(j = 0 ; j < 3; j++)
        {
            glNormal3f(m_faces[i].norm[j].vn[0],m_faces[i].norm[j].vn[1],m_faces[i].norm[j].vn[2]);
            glTexCoord2f(m_faces[i].coord[j].vt[0],m_faces[i].coord[j].vt[1]);
            glVertex3f(m_faces[i].p[j].x,m_faces[i].p[j].y,m_faces[i].p[j].z);
        }
        glEnd();

    }

}





void Loader::processMTL(std::string input)
{

    std::string identifier;
    std::string read; //for reading whole lines

    MTL mtlTemp;
    std::ifstream l_inMtl;

    //for reading in numbers to give to the mtl
    float ka0, ka1, ka2;
    float kd0, kd1, kd2;
    float ks0, ks1, ks2;

    //so that an empty mtl is not pushed back into the vector
    bool firstRun = true;

    l_inMtl.open(input);
    l_inMtl >> identifier;

    do{
        if(identifier == "#")
        {
            getline(l_inMtl,read);
        }
        else if(identifier == "newmtl")
        {
            //checks to see if it has run before if it has not run before don't push back the last read
            if (firstRun == false)
                m_mtl.push_back(mtlTemp);
            else 
                firstRun = false;


            l_inMtl >> identifier;
            mtlTemp.setName(identifier);
        }
        else if(identifier == "Ka")
        {
            l_inMtl >>ka0 >> ka1 >> ka2;
            mtlTemp.setKa(ka0,ka1,ka2);
        }
        else if(identifier == "Kd")
        {
            l_inMtl >> kd0 >>kd1 >> kd2;
            mtlTemp.setKd(kd0,kd1,kd2);
        }
        else if(identifier =="Ks")
        {
            l_inMtl >> ks0 >> ks1 >> ks2;
            mtlTemp.setKs(ks0, ks1, ks2);
        }
        else if(identifier == "map_Ka")
        {
            getline(l_inMtl,identifier);
            //l_inMtl >> identifier;
            mtlTemp.setLoc(identifier);
        }
        else
        {
            getline(l_inMtl,read);
            std::cout << "Not Processed MTL" << identifier << " " << read << std::endl;
        }
        l_inMtl >> identifier;
    }while(!l_inMtl.eof());

    l_inMtl.close();
    m_mtl.push_back(mtlTemp); // so the last one is pushed back

}