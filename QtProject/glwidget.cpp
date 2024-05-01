#include "glwidget.h"

#include <QMouseEvent>
#include <QOpenGLContext>
#include <simpleobject3d.h>
#include "group3d.h"
#include <QtMath>


float last_a1 = 0;
float last_a2 = 0;
float last_a3 = 0;

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{
    m_z = -10.0f;
}

void GLWidget::initializeGL()
{
    glClearColor(255.0f, 255.0f, 255.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
    //initCube(1.0f);
    m_groups.append(new Group3D); // 0 - Платформа
    m_groups.append(new Group3D); // 1 - Стержень + груз
    initSettedCube(8.0f, 2.0f, 4.0f, 0, 0.0, 0); // Платформа
   /// initSettedCube(0.25f, 6.0f, 0.25f, 0, 0.5, 0); // стержень
    //initSettedCube(1.0f, 1.0f, 1.0f, 0, 2.0, 0); // Груз

    m_groups[0]->addObject(m_objects[0]);
    ///m_groups[1]->addObject(m_objects[1]);
    //m_groups[1]->addObject(m_objects[2]);

    ///m_groups[1]->translate(QVector3D(-4.0f, 0.0f, 0.0f));

    m_TransformObjects.append(m_groups[0]);
    m_TransformObjects.append(m_groups[1]);

    m_timer.start(30, this);
}

void GLWidget::resizeGL(int w, int h)
{
    float aspect = w / (h ? (float)h : 1);

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45, aspect, 0.01f, 100.0f);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    viewMatrix.translate(0.0f, 0.0f, m_z);
    viewMatrix.rotate(m_rotation);

    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();

    m_program.bind();
    m_program.setUniformValue("u_projectionMatrix", m_projectionMatrix);
    m_program.setUniformValue("u_viewMatrix", viewMatrix);
    m_program.setUniformValue("u_lightPosition", QVector4D(0.0, 0.0, 0.0, 1.0));
    m_program.setUniformValue("u_lightPower", 1.0f);

    for(int i = 0; i< m_TransformObjects.size(); ++i){
        m_TransformObjects[i]->draw(&m_program, context()->functions());
    }
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
        m_mousePosition = QVector2D(event->position());
    event->accept();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() != Qt::LeftButton)
        return;
    QVector2D diff = QVector2D(event->position()) - m_mousePosition;
    m_mousePosition = QVector2D(event->position());

    float angle = diff.length() / 2.0;

    QVector3D axis = QVector3D(diff.y(), diff.x(), 0.0);

    m_rotation = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotation;

    update();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().ry() > 0){
        m_z += 0.25;
    }
    else if(event->angleDelta().ry() < 0){
        m_z -= 0.25;
    }
    update();
}

void GLWidget::timerEvent(QTimerEvent *event)
{
    auto rotation = QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, qSin(angleObject));
    m_groups[1]->rotate(rotation);
    angleObject += M_PI / 15;

    m_groups[1]->translate(QVector3D(step, 0.0, 0.0));
    if(pos < -4)
        step = 0.1;
    if(pos > 4)
        step = -0.1;
    pos += step;
    update();
    //qDebug() << angleObject;
}

void GLWidget::dataEvent(float a1, float a2, float a3){
    qDebug() << "rotate 3 angles";
    //auto rotation1 = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, a1 - last_a1);
    //auto rotation2 = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, a2 - last_a2); // чет не так
    //auto rotation3 = QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, a3 - last_a3); // чет не так
    auto rotation = QQuaternion::fromEulerAngles(a3 - last_a3, a2 - last_a2, a1 - last_a1);
    //m_groups[0]->rotate(rotation1);
    //m_groups[0]->rotate(rotation2);
    //m_groups[0]->rotate(rotation3);
    m_groups[0]->rotate(rotation);
    last_a1 = a1;
    last_a2 = a2;
    last_a3 = a3;
    update();
}

void GLWidget::initShaders()
{
    if(!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh"))
        close();

    if(!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh"))
        close();

    if(!m_program.link())
        close();
}

void GLWidget::initCube(float win_width)
{
    float width_div_2 = win_width / 2.0f;
    QVector<VertexData> vertexes;
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));


    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(0.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(1.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, -1.0, 0.0)));

    QVector<GLuint> indexes;
    for(int i = 0; i < 24; i+=4){
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);
        indexes.append(i + 2);
        indexes.append(i + 1);
        indexes.append(i + 3);
    }

    m_objects.append(new SimpleObject3D(vertexes, indexes, QImage(":/cube.png")));
}

void GLWidget::initSettedCube(float width, float height, float length, float dx, float dy, float dz)
{
    float width_div_2 = width / 2.0f;
    float height_div_2 = height / 2.0f;
    float length_div_2 = length / 2.0f;

    QVector<VertexData> vertexes;
    vertexes.append(VertexData(QVector3D(-width_div_2 + dx, height_div_2 + dy, length_div_2 + dz), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2 + dx, -height_div_2 + dy, length_div_2 + dz), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2 + dx, height_div_2 + dy, length_div_2 + dz), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2 + dx, -height_div_2 + dy, length_div_2 + dz), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));

    vertexes.append(VertexData(QVector3D(width_div_2 + dx, height_div_2 + dy, length_div_2 + dz), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2 + dx, -height_div_2 + dy, length_div_2 + dz), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2 + dx, height_div_2 + dy, -length_div_2 + dz), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2 + dx, -height_div_2 + dy, -length_div_2 + dz), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width_div_2 + dx, height_div_2 + dy, length_div_2 + dz), QVector2D(0.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2 + dx, height_div_2 + dy, -length_div_2 + dz), QVector2D(0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2 + dx, height_div_2 + dy, length_div_2 + dz), QVector2D(1.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2 + dx, height_div_2 + dy, -length_div_2 + dz), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));


    vertexes.append(VertexData(QVector3D(width_div_2 + dx, height_div_2 + dy, -length_div_2 + dz), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2 + dx, -height_div_2 + dy, -length_div_2 + dz), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2 + dx, height_div_2 + dy, -length_div_2 + dz), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2 + dx, -height_div_2 + dy, -length_div_2 + dz), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2 + dx, height_div_2 + dy, length_div_2 + dz), QVector2D(0.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2 + dx, height_div_2 + dy, -length_div_2 + dz), QVector2D(0.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2 + dx, -height_div_2 + dy, length_div_2 + dz), QVector2D(1.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2 + dx, -height_div_2 + dy, -length_div_2 + dz), QVector2D(1.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2 + dx, -height_div_2 + dy, length_div_2 + dz), QVector2D(0.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2 + dx, -height_div_2 + dy, -length_div_2 + dz), QVector2D(0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2 + dx, -height_div_2 + dy, length_div_2 + dz), QVector2D(1.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2 + dx, -height_div_2 + dy, -length_div_2 + dz), QVector2D(1.0, 0.0), QVector3D(0.0, -1.0, 0.0)));

    QVector<GLuint> indexes;
    for(int i = 0; i < 24; i+=4){
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);
        indexes.append(i + 2);
        indexes.append(i + 1);
        indexes.append(i + 3);
    }

    m_objects.append(new SimpleObject3D(vertexes, indexes, QImage(":/cube.png")));
}

