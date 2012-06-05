#include "mlogic.h"

MLogic::MLogic()
{
}

MLogic::~MLogic()
{
    delete gridt;
}

int** MLogic::GetGridT()
{
    return gridt;
}

int MLogic::GetM()
{
    return m;
}

int MLogic::GetN()
{
    return n;
}

bool MLogic::SetFN(const char* fn)
{
    filename=fn;
    return true;
}

bool MLogic::eval()
{
    this->init();
    recwave(sn,sm,1,0);
    recpath(en,em);
    return true;
}

bool MLogic::init()
{
    ifstream fin(filename);
    if (!fin)
    {
        return false;
    }

    fin >> n;
    fin >> m;

    gridt = new int * [n];
    epath = new int * [n];
    blocked = new int *[n];
    params = new int ** [n];
    for (int i=0;i<n;i++)
    {
        gridt[i] = new int [m];
        epath[i] = new int [m];
        blocked[i] = new int [m];
        params[i] = new int * [m];
        for (int j=0;j<m;j++)
        {
            params[i][j] = new int [2];
            fin >> gridt[i][j];
            epath[i][j]=0;
            blocked[i][j]=0;
            if (gridt[i][j]==1)
            {
                sn=i;
                sm=j;
            }
            if (gridt[i][j]==2)
            {
                en=i;
                em=j;
            }
            params[i][j][0]=-1;
            params[i][j][1]=0;
            if (gridt[i][j]>4)
            {
                blocked[i][j]=1;
                params[i][j][1]=10000;
            }

        }
    }

    return true;
}

int** MLogic::GetEPath()
{
    epath[sn][sm]=1;
    epath[en][em]=1;
    return epath;
}

int MLogic::recwave(int cn, int cm, int cw, int cs)
{
    params[sn][sm][0]=0;
    params[sn][sm][1]=0;
    blocked[sn][sm]=0;
    int counter=0,d1=0,d2=0;
    int way=0,prevway=0;
    int min=10000,prevmin=10000;
    while (params[en][em][0]==-1)
    {
        for (int i=0;i<n;i++)
            for (int j=0;j<m;j++)
                if (params[i][j][0]!=-1 && params[i][j][0]!=counter)
                {

                    if (counter-1==params[i][j][0] && !(i==sn && j==sm))
                    {
                        way=0;
                        min=10000;
                        if (i<n-1 && !blocked[i+1][j] && params[i+1][j][0]==counter-2)
                        {
                            if (params[i+1][j][1]<min && !blocked[i+1][j] && gridt[i][j]!=4)
                            {
                                min=params[i+1][j][1];
                                way=1;
                            }
                        }
                        if (i>0 && !blocked[i-1][j] && params[i-1][j][0]==counter-2)
                        {
                            if (params[i-1][j][1]<min && !blocked[i-1][j] && gridt[i][j]!=4)
                            {
                                min=params[i-1][j][1];
                                way=2;
                            }
                        }
                        if (j<m-1 && !blocked[i][j+1] && params[i][j+1][0]==counter-2)
                        {
                            if (params[i][j+1][1]<min && !blocked[i][j+1] && gridt[i][j]!=3)
                            {
                                min=params[i][j+1][1];
                                way=3;
                            }
                        }
                        if (j>0 && !blocked[i][j-1] && params[i][j-1][0]==counter-2)
                        {
                            if (params[i][j-1][1]<min && !blocked[i][j-1] && gridt[i][j]!=3)
                            {
                                min=params[i][j-1][1];
                                way=4;
                            }
                        }
                        params[i][j][1]+=min+1;

                        if ((way==1 || way==2)&& gridt[i][j]==3) params[i][j][1]+=5;
                        if ((way==1 || way==2)&& j<n-1 && gridt[i][j+1]==4) params[i][j][1]+=5;
                        if ((way==1 || way==2)&& j>0 && gridt[i][j-1]==4) params[i][j][1]+=5;

                        if ((way==3 || way==4)&& gridt[i][j]==4) params[i][j][1]+=5;
                        if ((way==3 || way==4)&& i<n-1 && gridt[i+1][j]==3) params[i][j][1]+=5;
                        if ((way==3 || way==4)&& i>0 && gridt[i-1][j]==3) params[i][j][1]+=5;

                        if (params[i][j][0]>1)
                        {
                            prevmin=10000;
                            prevway=0;
                            switch (way)
                            {
                            case 1:
                                d1=1;
                                d2=0;break;
                            case 2:
                                d1=-1;
                                d2=0;break;
                            case 3:
                                d1=0;
                                d2=1;break;
                            case 4:
                                d1=0;
                                d2=-1;break;
                            }

                            if ((i+1+d1>0 && i+1+d1<n) && (j+d2>0 && j+d2<m) && params[i+1+d1][j+d2][1]<min /*&& gridt[i+d1][j+d2]!=4*/) {prevmin=params[i+1+d1][j+d2][1];prevway=1;}
                            if ((i-1+d1>0 && i-1+d1<n) && (j+d2>0 && j+d2<m) && params[i-1+d1][j+d2][1]<min /*&& gridt[i+d1][j+d2]!=4*/) {prevmin=params[i-1+d1][j+d2][1];prevway=2;}
                            if ((i+d1>0 && i+d1<n) && (j+1+d2>0 && j+1+d2<m) && params[i+d1][j+1+d2][1]<min /*&& gridt[i+d1][j+d2]!=3*/) {prevmin=params[i+d1][j+1+d2][1];prevway=3;}
                            if ((i+d1>0 && i+d1<n) && (j-1+d2>0 && j-1+d2<m) && params[i+d1][j-1+d2][1]<min /*&& gridt[i+d1][j+d2]!=3*/) {prevmin=params[i+d1][j-1+d2][1];prevway=4;}

                            if ((way == 1 || way ==2) && (prevway==3 || prevway==4)) params[i][j][1]+=2;
                            if ((way == 3 || way ==4) && (prevway==1 || prevway==2)) params[i][j][1]+=2;
                        }
                    }
                    if (i<n-1 && !blocked[i+1][j] && params[i+1][j][0]==-1) params[i+1][j][0]=counter;
                    if (i>0 && !blocked[i-1][j] && params[i-1][j][0]==-1) params[i-1][j][0]=counter;
                    if (j<m-1 && !blocked[i][j+1] && params[i][j+1][0]==-1) params[i][j+1][0]=counter;
                    if (j>0 && !blocked[i][j-1] && params[i][j-1][0]==-1) params[i][j-1][0]=counter;

                }
        counter++;
    }

    blocked[sn][sm]=1;

    for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++)
        {
            if(params[i][j][1]==0 && !blocked[i][j]) params[i][j][1]=10000;
        }
    }

}

bool MLogic::recpath(int cn, int cm)
{
    if (cn==sn && cm==sm) return true;
    int min=10000,tn=-1,tm=-1;
    if (cn<n-1 && params[cn+1][cm][1]<min && gridt[cn][cm]!=4)
    {
        min=params[cn+1][cm][1];
        tn=cn+1;
        tm=cm;
    }
    if (cn>0 && params[cn-1][cm][1]<min && gridt[cn][cm]!=4)
    {
        min=params[cn-1][cm][1];
        tn=cn-1;
        tm=cm;
    }
    if (cm<m-1 && params[cn][cm+1][1]<min && gridt[cn][cm]!=3)
    {
        min=params[cn][cm+1][1];
        tn=cn;
        tm=cm+1;
    }
    if (cm>0 && params[cn][cm-1][1]<min && gridt[cn][cm]!=3)
    {
        min=params[cn][cm-1][1];
        tn=cn;
        tm=cm-1;
    }
    if(tn==-1 || tm==-1) return true;
    epath[tn][tm]=1;
    recpath(tn,tm);
}

int*** MLogic::GetParams()
{
    return params;
}
