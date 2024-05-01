#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QBasicTimer>

class SimpleObject3D;
class Transformational;
class Group3D;

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);
    void dataEvent(float a1, float a2, float a3);
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void timerEvent(QTimerEvent *event);

    void initShaders();
    void initCube(float win_width);
    void initSettedCube(float width, float height, float lenght, float dx, float dy, float dz);

private:
    QMatrix4x4 m_projectionMatrix;
    QOpenGLShaderProgram m_program;
    QVector2D m_mousePosition;
    QQuaternion m_rotation;

    QVector<SimpleObject3D *> m_objects;
    QVector<Group3D *> m_groups;
    QVector<Transformational *> m_TransformObjects;

    float m_z;

    QBasicTimer m_timer;

    float angleObject=0; // угол стержня + груза
    float pos=-4; // позиция
    float step = 0.1;
};

#endif // GLWIDGET_H
