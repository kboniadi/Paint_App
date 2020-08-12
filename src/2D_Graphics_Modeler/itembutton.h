#ifndef ITEMBUTTON_H
#define ITEMBUTTON_H

#include <QPushButton>
#include <QWidget>

namespace Ui {
class ItemButton;
}

class ItemButton : public QWidget
{
	Q_OBJECT

public:
	/**
	 * @brief PosButton
	 * @param parent
	 */
	explicit ItemButton(const QList<QPair<QIcon, QString>> &buttons, QWidget *parent = nullptr);

	/**
	 * @brief Destructor
	 */
	~ItemButton();

	QPushButton* button(int i);
signals:
	void clicked(int i);
private:
	QVector<QPushButton*> buttons;
	Ui::ItemButton *ui;
};

#endif // ITEMBUTTON_H
