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

// Qt
#include <QtGui>

// CC
#include "qtablewidget.h"
#include "ccGLWindow.h"
#include "ccPickingHub.h"
#include "ccHObject.h"
#include "DistanceComputationTools.h"
#include "ccScalarField.h"
#include "ccPlane.h"

// Local dependencies
#include "qMPlane.h"

qMPlane::qMPlane( QObject *parent )
	: QObject( parent )
	, ccStdPluginInterface( ":/CC/plugin/qMPlane/info.json" )
	, m_action( nullptr )
{
}

QList<QAction *> qMPlane::getActions()
{
	if (!m_action)
	{
		m_action = new QAction(getName(), this);
		m_action->setToolTip(getDescription());
		m_action->setIcon(getIcon());
		connect(m_action, &QAction::triggered, this, &qMPlane::doAction);
	}
	return{ m_action };
}

// Called when an item is selected
void qMPlane::onNewSelection( const ccHObject::Container &selectedEntities )
{
	if ( m_action == nullptr )
	{
		return;
	}

	m_action->setEnabled(false);
	if(selectedEntities.size() == 1) {
		ccHObject *object = selectedEntities.at(0);
		if (object->getClassID() == CC_TYPES::POINT_CLOUD) {
			m_selectedCloud = static_cast<ccPointCloud*>(object);
			m_action->setEnabled(true);
		}
	}
}

// Called when plugin icon is clicked
void qMPlane::doAction()
{
	if (m_app == nullptr)
	{
		Q_ASSERT(false);
		return;
	}

	if (!m_controller) {
		m_controller = std::make_unique<ccMPlaneDlgController>(m_app);
	}
	m_controller->openDialog(m_selectedCloud);
}