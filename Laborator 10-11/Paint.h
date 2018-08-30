#pragma once
#include <qpainter>
class Paint :public QPainter{

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		p.drawLine(0, 0, width(), height());
		p.drawImage(x, 0, QImage("sky.jpg"));
		p.setPen(Qt::blue);
		p.setFont(QFont("Arial", 30));
		p.drawText(rect(), Qt::AlignTop | Qt::AlignHCenter, "Qt QPainter");
		p.fillRect(0, 100, 100, 100, Qt::BrushStyle::Dense1Pattern);
	}
}