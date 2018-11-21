//
// Created by Hanke on 2018/10/22.
//

#ifndef CAD_FINAL_VERTEX_H
#define CAD_FINAL_VERTEX_H

#include <eigen3/Eigen/Dense>

class Vertex {
public:
    Vertex();

    Vertex(const Eigen::Vector3d &pos);

    Vertex(const double &x, const double &y, const double &z);

    virtual ~Vertex();

    const Eigen::Vector3d &getPos() const;

    void setPos(const Eigen::Vector3d &pos);

    const Eigen::Vector3d &getNormal() const;

    void setNormal(const Eigen::Vector3d &normal);

    Vertex *getPrev_v() const;

    void setPrev_v(Vertex *prev_v);

    Vertex *getNext_v() const;

    void setNext_v(Vertex *next_v);

    void AddNewVertex();

    void AddNewVertex(const double &x, const double &y, const double &z);

    void PrintPos();

private:
    Eigen::Vector3d pos;
    Eigen::Vector3d normal;
    Vertex *prev_v;
    Vertex *next_v;
};


#endif //CAD_FINAL_VERTEX_H
