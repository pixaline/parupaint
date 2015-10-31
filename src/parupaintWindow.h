#ifndef PARUPAINTWINDOW_H
#define PARUPAINTWINDOW_H

#include "core/parupaintBrushGlass.h"

#include <QHash>
#include <QTabletEvent>
#include <QMainWindow>

class ParupaintCanvasView;
class ParupaintCanvasPool;
class ParupaintCanvasBrush;
class ParupaintCanvasBanner;

class ParupaintClientInstance;

class ParupaintChat;
class ParupaintFlayer;
class ParupaintColorPicker;
class ParupaintInfoBar;
class ParupaintKeys;

class QDropEvent;

enum OverlayStatus {
	OVERLAY_STATUS_HIDDEN,
	OVERLAY_STATUS_SHOWN_SMALL,
	OVERLAY_STATUS_SHOWN_NORMAL
};


class ParupaintWindow : public QMainWindow {
Q_OBJECT
	private:
	quint16 local_port;
	int old_brush_switch;

	ParupaintKeys *key_shortcuts;

	bool OverlayButtonDown;
	QTimer * OverlayTimer;
	QTimer * OverlayButtonTimer;

	void UpdateOverlay();
	
	OverlayStatus	OverlayState;

	QTimer * fillpreview_timer;
	
	ParupaintBrushGlass glass;

	ParupaintCanvasBanner * canvas_banner;
	ParupaintChat * chat;
	ParupaintFlayer * flayer;
	ParupaintColorPicker * picker;
	ParupaintInfoBar * infobar;

	void closeEvent(QCloseEvent * event);
	void mousePressEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent * event);
	void keyReleaseEvent(QKeyEvent * event);
	void resizeEvent(QResizeEvent * event);
	void dropEvent(QDropEvent *ev);
	void dragEnterEvent(QDragEnterEvent *ev);
	ParupaintCanvasView * view;
	ParupaintCanvasPool * pool;

	ParupaintClientInstance * client;

	public:
	~ParupaintWindow();
	ParupaintWindow();
	ParupaintCanvasPool * GetCanvasPool();

	void ShowOverlay(bool=true);
	void HideOverlay();

	void UpdateTitle();

	void SetLocalHostPort(quint16);
	QString GetSaveDirectory() const;

	// Dialogs
	void Connect(QString);
	void Disconnect();
	void Open(QString);
	QString SaveAs(QString);
	void New(int, int, bool=false);

	private slots:
	void VersionResponse(bool, QString);

	void Command(QString, QString);

	void OverlayTimeout();
	void ButtonTimeout();

	void ViewUpdate();

	void PenDrawStart(ParupaintBrush*);
	void PenMove(ParupaintBrush*);
	void PenDrawStop(ParupaintBrush*);
	void PenPointerType(QTabletEvent::PointerType old, QTabletEvent::PointerType nuw);

	void CursorChange(ParupaintBrush*);
	void ColorChange(QColor);

	void SelectFrame(int, int);
	void ChangedFrame(int, int);
	void ChatMessage(QString);

	void ChatMessageReceived(QString, QString);
	void OnNetworkDisconnect();
};


#endif
