/*
 * glwidget.h
 *
 *  Created on: Dec 31, 2008
 *      Author: Administrator
 */

#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QGLWidget>
#include <QtOpenGL>


class GLWidget: public QGLWidget
{
	Q_OBJECT
public:
	GLWidget(QWidget *parent=0);
	~GLWidget();

	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	void savePanoImage(QString fileName);
	void showPanoFromPic(QStringList srcList);
	void showPanoFromCam(int numCam);
	void showPanoFromVideo(QStringList srcList);
	void startRec(QString fileName);
	void stopRec();

public slots:
	void animate();

signals:

protected:
	void initializeGL();
	void paintGL();
	int *numMapping;
	void resizeGL(int width,int height);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);


private:
    GLuint object;
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
    QPointF *picPosition;
    QColor trolltechGreen;
    QColor trolltechPurple;
//    void initPineApple();

};

#endif /* GLWIDGET_H_ */
