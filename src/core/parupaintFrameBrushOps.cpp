
#include "parupaintFrameBrushOps.h"
#include "parupaintFrame.h"
#include "parupaintBrush.h"

#include <QtMath>
#include <QDebug>

QRect ParupaintFrameBrushOps::stroke(float ox, float oy, float nx, float ny, ParupaintBrush * brush, ParupaintFrame * frame)
{
	if(!frame) return QRect();

	auto width = brush->GetPressureWidth();
	auto color = brush->GetColor();
	QRect urect(ox - width, oy - width, ox + width, oy + width);
	urect |= QRect(nx - width, ny - width, nx + width, ny + width);

	switch(brush->GetToolType()){
		case 1:
		{
			frame->Fill(nx, ny, brush->GetColor());
			return frame->GetImage().rect();
		}
		case 2:
		{
			QColor d_col = brush->GetColor();
			d_col.setAlphaF(0.1);
			const float dot_width = 1 + (brush->GetPressure() > 0.75 ? brush->GetPressure() * 2 : 0);

			for(int x = 0; x < width; x++){
				for(int y = 0; y < width/2; y++){
					const double aa = (double(x) / width) * M_PI;
					const int ax = int(nx) + qRound(cos(aa) * width/2);
					const int ay = int(ny) + qRound(sin(aa) * y);
					const int ay2 = int(ny) - qRound(sin(aa) * y);
					const int m = 10; // every nth pixel

					if(ax % m == 0){
						if(ay % m == 0)
							frame->DrawStep(ax, ay, ax+1, ay+1, dot_width, d_col);
						if(ay2 % m == 0)
							frame->DrawStep(ax, ay2, ax+1, ay2+1, dot_width, d_col);
					}
				}
			}
			return urect;
		}

		// carries on to default
		case 3: color.setAlphaF(brush->GetPressure());
		default:
		{
			frame->DrawStep(ox, oy, nx, ny, width, color);
			return urect;
		}
	}
	return QRect();
}
