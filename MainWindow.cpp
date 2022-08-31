#include "MainWindow.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "SceneView.h"

MainWindow::MainWindow():
#ifdef Q_OS_WIN
    QDialog(nullptr, Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)
#else
    QDialog(nullptr, Qt::Window)
#endif
{
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3,3);
    format.setSamples(4);	// enable multisampling (antialiasing)
    format.setDepthBufferSize(8);

    m_sceneView = new SceneView;
    m_sceneView->setFormat(format);

        // *** create window container widget

    QWidget *container = QWidget::createWindowContainer(m_sceneView);
    container->setFocusPolicy(Qt::TabFocus);
    container->setMinimumSize(QSize(640,400));

        // *** create the layout and insert widget container

    QVBoxLayout * vlay = new QVBoxLayout;
    //vlay->setMargin(0);
    vlay->setSpacing(0);
    vlay->addWidget(container);

    // now create some buttons at the bottom

    QHBoxLayout * hlay = new QHBoxLayout;
    //hlay->setCanvasMargin(0);

    QLabel * navigationInfo = new QLabel(this);
    navigationInfo->setWordWrap(true);
    navigationInfo->setText("Hold right mouse button for free mouse look and to navigate "
                                "with keys WASDCtrlSpace. Hold shift to slow down. Use scroll-wheel to move quickly forward and backward.");
    hlay->addWidget(navigationInfo);

    QPushButton * closeBtn = new QPushButton(tr("Close"), this);
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);

    hlay->addWidget(closeBtn);
    hlay->setStretch(0,1);

    vlay->addLayout(hlay);

    setLayout(vlay);

    resize(700,450);

    container->setFocus();
}
