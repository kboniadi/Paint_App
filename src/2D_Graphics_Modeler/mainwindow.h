#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QLabel>
#include "login.h"
#include "about.h"
#include "storage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * @class MainWindow
 * @brief MainWindow class inherits QMainWindow and represents the central ui.
 * Manages 4 attributes.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief initializes MainWindow with parent QWidget
     * \param parent QWidget (defaults to nullptr)
     */
    MainWindow(QWidget *parent = nullptr);

    /*!
     * \brief destructor, deletes ui
     */
    ~MainWindow();

    /*!
     * \brief sets renderArea's cursor
     */
    void SetDrawCursor(const QCursor&);
	void SetStatusBar(const QString&, int timeout = 0);
signals:
	void onCanvasClick(int x, int y);
	void onCanvasDoubleClick(int x, int y);
	void onCanvasDrag(int x, int y);
protected:
    /*!
     * \brief accpets the close event
     * \param close event
     */
	void closeEvent(QCloseEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
private slots:

	void on_shapeList_currentIndexChanged(int index);

	void onDataChanged();
    /*!
     * \brief slot for actionLogin
     *        shows Login window
     */
	void on_actionLogin_triggered();

    /*!
     * \brief slot for actionExit
     *        closes MainWindow
     */
	void on_actionExit_triggered();

    /*!
     * \brief slot for actionAbout
     *        shows About window
     */
    void on_actionAbout_triggered();

    /*!
     * \brief slot for actionAdd_Rectangle
     *        adds default Rectangle to renderArea
     */
    void on_actionAdd_Rectangle_triggered();

    /*!
     * \brief slot for actionAdd_Ellipse
     *        adds default Ellipse to renderArea
     */
    void on_actionAdd_Ellipse_triggered();

    /*!
     * \brief slot for actionAdd_Polygon
     *        adds default Polygon to renderArea
     */
    void on_actionAdd_Polygon_triggered();

    /*!
     * \brief slot for actionAdd_Polyline
     *        adds default Polyline to renderArea
     */
    void on_actionAdd_Polyline_triggered();

    /*!
     * \brief slot for actionAdd_Line
     *        adds default Line to renderArea
     */
    void on_actionAdd_Line_triggered();

    /*!
     * \brief slot for actionAdd_Text
     *        adds default Text to renderArea
     */
    void on_actionAdd_Text_triggered();

    /*!
     * \brief slot for actionLogout
     *        logs out and removes admin rights
     */
    void on_actionLogout_triggered();

    /*!
     * \brief slot actionDelete
     *        shows delete shape dialog
     */
	void on_actionDelete_triggered();

    /*!
     * \brief move the shape when 'Ok' is pressed in the "Move" dialogue
     */
	void on_actionMove_triggered();
	void on_actionNew_triggered();

private:
	template<class T>
	void AddRect(int x, int y);
	/*!
	 * @brief activates or deactivates the setEnabled() functions in
	 * actionLogin or action logout
	 * @param (bool) value that controls the current user permissions
	 */
	void Disconnect();
	void DisconnectDoubleClick();
	void DisconnectDrag();
	void SetAdminRights(bool);

	Storage storage;
	Ui::MainWindow *ui;			//!< ptr to the mainWindow UI
	QList<QObject*> adminFeats;	//!< list of action_triggers that only
								//!< admin can use
	QLabel status;
	bool modified;
};
#endif // MAINWINDOW_H
