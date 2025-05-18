// GRAPHICS.h
// Language C++
// Version 1.000
// Date: 21 - MAY - 2024
// MIT LICENSE

// Copyright <2024> <James C Williams>

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
// documentation files(the “Software”), to deal in the Software without restriction, including without 
// limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of 
// the Software, and to permit persons to whom the Software is furnished to do so, subject to the following 
// conditions :

// The above copyright notice and this permission notice shall be included in all copies or substantial portions 
// of the Software.

// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED 
// TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL 
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
// CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
// DEALINGS IN THE SOFTWARE.




// GRAPHICS PACKAGE





#pragma once
#ifndef GRAPHICS
#define GRAPHICS

class Color
{
public:
    friend class Point;
    friend class Line;
    

    typedef double GLdouble;
    typedef float GLfloat;

    Color(GLdouble red, GLdouble grn, GLdouble blu, GLdouble msk)
    {
        coord[3] = msk;
        coord[0] = red;
        coord[1] = grn;
        coord[2] = blu;
    }

    ~Color()
    {
        delete[] coord;
    }

    GLdouble access(int i)const
    {
        return coord[i];
    }
    void load(int i, GLdouble c)
    {
        coord[i] = c;
    }
private:
    GLdouble coord[4];
};




class Point
{
    friend class Transform;
    friend class PointList;
    friend class Point;
    friend class Line;
public:

    typedef double GLdouble;
    typedef float GLfloat;

    Point(GLdouble xx, GLdouble yy, GLdouble zz)
    {
        coord[0] = xx;
        coord[1] = yy;
        coord[2] = zz;
        coord[3] = 1.;
    }
    Point()
    {
        coord[0] = 0.;
        coord[1] = 0.;
        coord[2] = 0.;
        coord[3] = 1.;
    }
    ~Point() {}

    // Mathematical operations with Point:

    Point operator= (const Point& p)
    {
        coord[0] = p.coord[0];
        coord[1] = p.coord[1];
        coord[2] = p.coord[2];
        coord[3] = p.coord[3];
        return *this;
    }
    Point operator+ (const Point& p)
    {
        return Point(coord[0] + p.coord[0], coord[1] + p.coord[1], coord[2] + p.coord[2]);
    }
    Point operator- (const Point& p)
    {
        return Point(coord[0] - p.coord[0], coord[1] - p.coord[1], coord[2] - p.coord[2]);
    }
    Point operator* (const Point& p)
    {
        return Point(coord[0] * p.coord[0], coord[1] * p.coord[1], coord[2] * p.coord[2]);
    }
    Point operator* (const GLdouble ww)
    {
        return Point(coord[0] * ww, coord[1] * ww, coord[2] * ww);
    }
    Point operator/ (const Point& p)
    {
        GLdouble r = 0.;
        GLdouble s = 0.;
        GLdouble t = 0.;
        if (p.coord[0] != 0.) { r = coord[0] / p.coord[0]; }
        if (p.coord[1] != 0.) { s = coord[1] / p.coord[1]; }
        if (p.coord[2] != 0.) { t = coord[2] / p.coord[2]; }
        return Point(r, s, t);
    }
    Point operator/ (const GLdouble& ww)
    {
        if (ww == 0.) return Point(0., 0., 0.);
        return Point(coord[0] / ww, coord[1] / ww, coord[2] / ww);
    }
    GLdouble metric(const Point& p)const
    {
        return (sqrt((coord[0] - p.coord[0]) * (coord[0] - p.coord[0]) + (coord[1] -
            p.coord[1]) * (coord[1] - p.coord[1]) + (coord[2] - p.coord[2]) * (coord[2] -
                p.coord[2])));
    }

    // Access to Point.coord:

    GLdouble access(int c)const 
        { 
        return coord[c]; 
        }
    void load(int c, GLdouble ww) 
        { 
        coord[c] = ww; 
        }

private:
    GLdouble coord[4];

};

#endif


int POINTLIST_N = 1;

class PointList
{
    friend class Point;
    friend class Transform;

public:

    typedef double GLdouble;
    typedef float GLfloat;

    PointList(int i)
    {
        n = i;
        list = new Point[n]();
    }
    PointList()
    {
        n = POINTLIST_N;
        list = new Point[POINTLIST_N]();
    }
    ~PointList()
    {
        delete[] list;
    }

    // Mathematical operations with PointList:class

    PointList same(int i, PointList p)
    {
        list[i] = p.list[i];
        i++;
        if (i < p.n) return p.same(i, p);
        return *this;
    }
    PointList operator= (PointList p)
    {
        int i = 0;
        n = p.n;
        return p.same(i, p);
        return *this;
    }

    // Access to PointList..[]:

    GLdouble access(int i, int c)
    {
        return list[i].access(c);
    }
    void load(int i, int c, GLdouble ww)
    {
        list[i].load(c, ww);
    }
    Point access(int i)
    {
        return list[i];
    }
    void load(int i, Point p)
    {
        list[i] = p;
    }
    GLdouble index()const
    {
        return n;
    }

private:
    Point* list;
    int n;
};

class Line
{
public:
    friend class Point;
    friend class Transform;
    friend class Color;

    typedef double GLdouble;
    typedef float GLfloat;

    Line(GLdouble xx, GLdouble yy, GLdouble zz, GLdouble xx2, GLdouble yy2, GLdouble zz2)
    {
        p1.coord[0] = xx;
        p1.coord[1] = yy;
        p1.coord[2] = zz;
        p2.coord[0] = xx2;
        p2.coord[1] = yy2;
        p2.coord[2] = zz2;
    }
    Line(Point& p, Point& q)
    {
        p1.coord[0] = p.coord[0];
        p1.coord[1] = p.coord[1];
        p1.coord[2] = p.coord[2];
        p2.coord[0] = q.coord[0];
        p2.coord[1] = q.coord[1];
        p2.coord[2] = q.coord[2];
    }
    Line()
    {

    }
    ~Line()
    {
    }

    // Mathematical operations with Line:

    Line operator= (const Line& l)
    {
        p1.coord[0] = l.p1.coord[0];
        p1.coord[1] = l.p1.coord[1];
        p1.coord[2] = l.p1.coord[2];
        p1.coord[3] = l.p1.coord[3];
        p2.coord[0] = l.p2.coord[0];
        p2.coord[1] = l.p2.coord[1];
        p2.coord[2] = l.p2.coord[2];
        p2.coord[3] = l.p2.coord[3];
        return *this;
    }
    Line operator+ (const Line& l)
    {
        return Line(p1.coord[0] + l.p1.coord[0], p1.coord[1] + l.p1.coord[1],
            p1.coord[2] + l.p1.coord[2], p2.coord[0] + l.p2.coord[0],
            p2.coord[1] + l.p2.coord[1], p2.coord[2] + l.p2.coord[2]);
    }
    Line operator- (const Line& l)
    {
        return Line(p1.coord[0] - l.p1.coord[0], p1.coord[1] - l.p1.coord[1],
            p1.coord[2] - l.p1.coord[2], p2.coord[0] - l.p2.coord[0],
            p2.coord[1] - l.p2.coord[1], p2.coord[2] - l.p2.coord[2]);
    }
    Line operator* (const Line& l)
    {
        return Line(p1.coord[0] * l.p1.coord[0], p1.coord[1] * l.p1.coord[1],
            p1.coord[2] * l.p1.coord[2], p2.coord[0] * l.p2.coord[0],
            p2.coord[1] * l.p2.coord[1], p2.coord[2] * l.p2.coord[2]);
    }
    Line operator* (const GLdouble& ww)
    {
        return Line(p1.coord[0] * ww, p1.coord[1] * ww, p1.coord[2] * ww,
            p2.coord[0] * ww, p2.coord[1] * ww, p2.coord[2] * ww);
    }
    Line operator/ (const Line& l)
    {
        GLdouble r1 = 0.;
        GLdouble s1 = 0.;
        GLdouble t1 = 0.;
        GLdouble r2 = 0.;
        GLdouble s2 = 0.;
        GLdouble t2 = 0.;
        if (l.p1.coord[0] != 0.) { r1 = p1.coord[0] / l.p1.coord[0]; }
        if (l.p1.coord[1] != 0.) { s1 = p1.coord[1] / l.p1.coord[1]; }
        if (l.p1.coord[2] != 0.) { t1 = p1.coord[2] / l.p1.coord[2]; }
        if (l.p2.coord[0] != 0.) { r2 = p2.coord[0] / l.p2.coord[0]; }
        if (l.p2.coord[1] != 0.) { s2 = p2.coord[1] / l.p2.coord[1]; }
        if (l.p2.coord[2] != 0.) { t2 = p2.coord[2] / l.p2.coord[2]; }
        return Line(r1, s1, t1, r2, s2, t2);
    }
    Line operator/ (const GLdouble& ww)
    {
        if (ww == 0.) return Line(0., 0., 0., 0., 0., 0.);
        return Line(p1.coord[0] / ww, p1.coord[1] / ww, p1.coord[2] / ww,
            p2.coord[0] / ww, p2.coord[1] / ww, p2.coord[2] / ww);
    }

    // Access to Line..coord:

    GLdouble access(int d, int c)const
    {
        if (d == 1) return p1.coord[c];
        if (d == 2) return p2.coord[c];
        return 0.;
    }
    void load(int d, int c, GLdouble ww)
    {
        if (d == 1) p1.coord[c] = ww;
        if (d == 2) p2.coord[c] = ww;
        return;
    }
    Point access(int d)const
    {
        if (d == 1)
        {
            return p1;
        }
        if (d == 2)
        {
            return p2;
        }
    }
    void load(Point p, Point q)
    {
        p1 = p;
        p2 = q;
    }
private:
    Point p1, p2;
};


int LINELIST_N = 1;

class LineList
{
    friend class Point;
    friend class Transform;
    friend class Line;
    friend class Color;

public:

    typedef double GLdouble;
    typedef float GLfloat;

    LineList(int i)
    {
        n = i;
        list = new Line[n]();
    }
    LineList()
    {
        n = POINTLIST_N;
        list = new Line[POINTLIST_N]();
    }
    ~LineList()
    {
        delete[] list;
    }

    // Mathematical operations with LineList:class

    LineList same(int i, LineList p)
    {
        list[i] = p.list[i];
        i++;
        if (i < p.n) return p.same(i, p);
        return *this;
    }
    LineList operator= (LineList p)
    {
        int i = 0;
        n = p.n;
        return p.same(i, p);
        return *this;
    }

    // Access to LineList..[]:

    GLdouble access(int i, int d, int c)
    {
        return list[i].access(d,c);
    }
    void load(int i, int d, int c, GLdouble ww)
    {
        list[i].load(d, c, ww);
    }
    Line access(int i)
    {
        return list[i];
    }
    void load(int i, Line p)
    {
        list[i] = p;
    }
    GLdouble index()const
    {
        return n;
    }

private:
    Line* list;
    int n;
};




int POLYGON_N = 1;

class Polygone
{
public:
    friend class Point;
    friend class Color;
    friend class PolygonList;

    typedef double GLdouble;
    typedef float GLfloat;

    Polygone(int i)
    {
        n = i;
        list = new Point[n];
    }
    Polygone()
    {
        n = POLYGON_N;
        list = new Point[POLYGON_N];
    }
    ~Polygone()
    {
        delete[] list;
    }

    //Mathematical operations with Polygon:

    Polygone& equal(int& i, Polygone& p)
    {
        list[i] = p.list[i];
        i++;
        if (i < n) return equal(i, p);
        return *this;
    }
    Polygone& operator= (Polygone& p)
    {
        int i = 0;
        n = p.n;
        list[i] = p.list[i];
        i++;
        if (i < n) return equal(i, p);
        return *this;
    }

    //Access to Polygon..coord:

    GLdouble access(int m, int c)
    {
        return list[m].access(c);
    }
    void load(int m, int c, GLdouble ww)
    {
        list[m].load(c, ww);
    }
    Point access(int m)
    {
        return list[m];
    }
    void load(const int& m, const Point& p)
    {
        list[m] = p;
    }
    int index()const
    {
        return n;
    }

private:
    Point* list;
    int n;
};


int FACELIST_M = 1;

class FaceList
{
    friend class Point;
    friend class Polygone;

    typedef double GLdouble;
    typedef float GLfloat;
public:
    FaceList(int i)
    {
        n = i;
        list = new Polygone[n];
    }
    FaceList()
    {
        m = FACELIST_M;
        list = new Polygone[m];
    }
    ~FaceList()
    {
        delete[] list;
    }

    // Mathematical operations with FaceList:

    FaceList equal(int& i, FaceList p)
    {
        list[i] = p.list[i];
        i++;
        if (i < p.n) return p.equal(i, p);
        return *this;
    }
    FaceList operator= (FaceList p)
    {
        int i = 0;
        n = p.n;
        return p.equal(i, p);
        return *this;
    }

    // Access to FaceList..[]:

    Polygone acceass(const int i)
    {
        return list[i];
    }
    void load(int i, Polygone p)
    {
        list[i] = p;
    }
    GLdouble index()const
    {
        return n;
    }
    void load(GLdouble& ww)
    {
        n = ww;
    }

private:
    Polygone* list;
    int n,m;



};



// Transform.h
// Translate, Scale, RotateX, RotateY, RotateZ
// AUTHOR: James C Williams
// DATE: 25 - JUN - 01
// Copyright (c) 2001
// Revision: 0.00


// temp_transform is a temporary class used to speed the Transform
// multiplication process:

class temp_transform
{
    friend class Transform;
    friend class Point;

    typedef double GLdouble;
    typedef float GLfloat;
public:
    temp_transform() {}
    ~temp_transform() {}
private:
    GLdouble d[4][4];
};

class Transform
{
    friend class temp_transform;
    friend class Point;
    friend class PointList;

    typedef double GLdouble;
    typedef float GLfloat;

    // constructors:

public:
    Transform()
    {
        d[0][0] = 1.;
        d[0][1] = 0.;
        d[0][2] = 0.;
        d[0][3] = 0.;
        d[1][0] = 0.;
        d[1][1] = 1.;
        d[1][2] = 0.;
        d[1][3] = 0.;
        d[2][0] = 0.;
        d[2][1] = 0.;
        d[2][2] = 1.;
        d[2][3] = 0.;
        d[3][0] = 0.;
        d[3][1] = 0.;
        d[3][2] = 0.;
        d[3][3] = 1.;
    }
    ~Transform(){}

    // Mathematical operations with Transform:

    Point operator() (const Point& p)
    {
        
        g = d[0][0] * p.coord[0] + d[0][1] * p.coord[1] + d[0][2] * p.coord[2] + d[0][3] * p.coord[3];
        r.load(0, g);
        g = d[1][0] * p.coord[0] + d[1][1] * p.coord[1] + d[1][2] * p.coord[2] + d[1][3] * p.coord[3];
        r.load(1, g);
        g = d[2][0] * p.coord[0] + d[2][1] * p.coord[1] + d[2][2] * p.coord[2] + d[2][3] * p.coord[3];
        r.load(2, g);
        g = d[3][0] * p.coord[0] + d[3][1] * p.coord[1] + d[3][2] * p.coord[2] + d[3][3] * p.coord[3];
        r.load(3, g);
        return r;
    }
    Transform operator= (const Transform& t)
    {
        d[0][0] = t.d[0][0];
        d[0][1] = t.d[0][1];
        d[0][2] = t.d[0][2];
        d[0][3] = t.d[0][3];
        d[1][0] = t.d[1][0];
        d[1][1] = t.d[1][1];
        d[1][2] = t.d[1][2];
        d[1][3] = t.d[1][3];
        d[2][0] = t.d[2][0];
        d[2][1] = t.d[2][1];
        d[2][2] = t.d[2][2];
        d[2][3] = t.d[2][3];
        d[3][0] = t.d[3][0];
        d[3][1] = t.d[3][1];
        d[3][2] = t.d[3][2];
        d[3][3] = t.d[3][3];
        return *this;
    }
    Transform operator= (const temp_transform& t)
    {
        d[0][0] = t.d[0][0];
        d[0][1] = t.d[0][1];
        d[0][2] = t.d[0][2];
        d[0][3] = t.d[0][3];
        d[1][0] = t.d[1][0];
        d[1][1] = t.d[1][1];
        d[1][2] = t.d[1][2];
        d[1][3] = t.d[1][3];
        d[2][0] = t.d[2][0];
        d[2][1] = t.d[2][1];
        d[2][2] = t.d[2][2];
        d[2][3] = t.d[2][3];
        d[3][0] = t.d[3][0];
        d[3][1] = t.d[3][1];
        d[3][2] = t.d[3][2];
        d[3][3] = t.d[3][3];
        return *this;
    }
    temp_transform operator* (const Transform& t)
    {
        q.d[0][0] = d[0][0] * t.d[0][0] + d[0][1] * t.d[1][0] + d[0][2] * t.d[2][0] + d[0][3] * t.d[3][0];
        q.d[0][1] = d[0][0] * t.d[0][1] + d[0][1] * t.d[1][1] + d[0][2] * t.d[2][1] + d[0][3] * t.d[3][1];
        q.d[0][2] = d[0][0] * t.d[0][2] + d[0][1] * t.d[1][2] + d[0][2] * t.d[2][2] + d[0][3] * t.d[3][2];
        q.d[0][3] = d[0][0] * t.d[0][3] + d[0][1] * t.d[1][3] + d[0][2] * t.d[2][3] + d[0][3] * t.d[3][3];
        q.d[1][0] = d[1][0] * t.d[0][0] + d[1][1] * t.d[1][0] + d[1][2] * t.d[2][0] + d[1][3] * t.d[3][0];
        q.d[1][1] = d[1][0] * t.d[0][1] + d[1][1] * t.d[1][1] + d[1][2] * t.d[2][1] + d[1][3] * t.d[3][1];
        q.d[1][2] = d[1][0] * t.d[0][2] + d[1][1] * t.d[1][2] + d[1][2] * t.d[2][2] + d[1][3] * t.d[3][2];
        q.d[1][3] = d[1][0] * t.d[0][3] + d[1][1] * t.d[1][3] + d[1][2] * t.d[2][3] + d[1][3] * t.d[3][3];
        q.d[2][0] = d[2][0] * t.d[0][0] + d[2][1] * t.d[1][0] + d[2][2] * t.d[2][0] + d[2][3] * t.d[3][0];
        q.d[2][1] = d[2][0] * t.d[0][1] + d[2][1] * t.d[1][1] + d[2][2] * t.d[2][1] + d[2][3] * t.d[3][1];
        q.d[2][2] = d[2][0] * t.d[0][2] + d[2][1] * t.d[1][2] + d[2][2] * t.d[2][2] + d[2][3] * t.d[3][2];
        q.d[2][3] = d[2][0] * t.d[0][3] + d[2][1] * t.d[1][3] + d[2][2] * t.d[2][3] + d[2][3] * t.d[3][3];
        q.d[3][0] = d[3][0] * t.d[0][0] + d[3][1] * t.d[1][0] + d[3][2] * t.d[2][0] + d[3][3] * t.d[3][0];
        q.d[3][1] = d[3][0] * t.d[0][1] + d[3][1] * t.d[1][1] + d[3][2] * t.d[2][1] + d[3][3] * t.d[3][1];
        q.d[3][2] = d[3][0] * t.d[0][2] + d[3][1] * t.d[1][2] + d[3][2] * t.d[2][2] + d[3][3] * t.d[3][2];
        q.d[3][3] = d[3][0] * t.d[0][3] + d[3][1] * t.d[1][3] + d[3][2] * t.d[2][3] + d[3][3] * t.d[3][3];
        return q;
    }

    // Access to Transform.coord:

    GLdouble index(int a, int b)const
    {
        return d[a][b];
    }
    void access(int a, int b, GLdouble w)
    {
        d[a][b] = w;
    }
    private:
        GLdouble g=0.;
protected:
    GLdouble d[4][4] = { 0 };
    Point r;
    temp_transform q;
};

class Translate : public Transform
{

    typedef double GLdouble;
    typedef float GLfloat;
public:
    Translate(GLdouble dx, GLdouble dy, GLdouble dz)
    {
        d[0][3] = dx;
        d[1][3] = dy;
        d[2][3] = dz;
    }
    Translate()
    {
        d[0][3] = 0.;
        d[1][3] = 0.;
        d[2][3] = 0.;
    }
};

class Scale : public Transform
{

    typedef double GLdouble;
    typedef float GLfloat;
public:
    Scale(GLdouble sx, GLdouble sy, GLdouble sz)
    {
        d[0][0] = sx;
        d[1][1] = sy;
        d[2][2] = sz;
    }
    Scale()
    {
        d[0][0] = 1.;
        d[1][1] = 1.;
        d[2][2] = 1.;
    }
};

class RotateX : public Transform
{

    typedef double GLdouble;
    typedef float GLfloat;
public:
    RotateX(GLdouble angle)
    {
        cc = cos(angle);
        ss = sin(angle);
        d[1][1] = cc;
        d[1][2] = 0. - ss;
        d[2][1] = ss;
        d[2][2] = cc;
    }
protected:
    GLdouble cc, ss;
};

class RotateY : public Transform
{

    typedef double GLdouble;
    typedef float GLfloat;
public:
    RotateY(GLdouble angle)
    {
        cc = cos(angle);
        ss = sin(angle);
        d[0][0] = cc;
        d[0][2] = ss;
        d[2][0] = 0. - ss;
        d[2][2] = cc;
    }
protected:
    GLdouble cc, ss;
};

class RotateZ : public Transform
{

    typedef double GLdouble;
    typedef float GLfloat;
public:
    RotateZ(GLdouble angle)
    {
        cc = cos(angle);
        ss = sin(angle);
        d[0][0] = cc;
        d[0][1] = 0. - ss;
        d[1][0] = ss;
        d[1][1] = cc;
    }
protected:
    GLdouble cc, ss;
};






