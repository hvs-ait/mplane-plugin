//##########################################################################
//#                                                                        #
//#                    CLOUDCOMPARE PLUGIN: qMPlane                        #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#         COPYRIGHT: AIT Austrian Institute of Technology GmbH           #
//#                                                                        #
//##########################################################################

#ifndef CC_MPLANE_DIALOG_HEADER
#define CC_MPLANE_DIALOG_HEADER

//Qt
#include <qtablewidget.h>
#include <qradiobutton.h>
#include <qcheckbox.h>

//CC
#include <ccGLWindow.h>
#include <ccOverlayDialog.h>

//Local
#include <ui_mplaneDlg.h>

// REMOVE!!!
#include "ccMainAppInterface.h"
//class encapsulating the map-mode overlay dialog
class ccMPlaneDlg : public ccOverlayDialog, public Ui::MPlaneDialog
{
	Q_OBJECT

public:
	//! Default constructor
	explicit ccMPlaneDlg(QWidget* parent = 0);

	// Point Fitting
	void initializeFittingPointTable();
	void addFittingPoint(int rowIndex, const CCVector3& point);
	void selectFittingPoint(unsigned int rowIndex);
	void clearFittingPoints();

	// Distance Measurement
	void addMeasurementPoint(const QString& name, float distance);
	void renameMeasurement(const QString& name, unsigned int rowIndex);
	void enableMeasurementTab(bool enable);
	void clearMeasurementPoints();
	bool isSignedMeasurement() const;
	bool isNormalVectorChecked() const;

private:
	void createPlaneFittingTab();
	void createMeasurementTab();
	int getFittingPointContentWidth() const;
	int getFittingPointTableWidth() const;
	QPushButton* createDeleteButton();

protected slots:
	void onMeasurementPointNameChanged(QTableWidgetItem *item);
	void onCloseButtonPressed();
	void onTabChanged(int tab);
	void onRadioButtonClicked();
	void onDeleteButtonClicked();
	void onShowNormalCheckBox(bool checked);
	void onSaveButtonClicked();

signals:
	void signalMeasureNameChanged(QTableWidgetItem *item);
	void signalCloseButtonPressed();
	void signalFittingPointClicked(int index);
	void signalTabChanged(int tab);
	void signalMeasurementModeChanged();
	void signalFittingPointDelete(int index);
	void signalShowNormalCheckBoxClicked(bool checked);
	void signalSaveButtonClicked();

private:
	QTabWidget *m_tabWidget = nullptr;

	// Point Selection Tab
	QWidget *m_tabPlaneFitting = nullptr;
	QTableWidget *m_pointTableWidget = nullptr;
	unsigned int m_pointTableMinWidth = 0;
	unsigned int m_pointTableMinHeight = 0;

	// Measurement Tab
	QWidget *m_tabMeasurement = nullptr;
	QTableWidget *m_measurementTableWidget = nullptr;
	QRadioButton *m_radioButtonSignedMeasurement = nullptr;
	QRadioButton *m_radioButtonUnsignedMeasurement = nullptr;
	QCheckBox *m_checkBoxShowNormal = nullptr;
};

#endif
