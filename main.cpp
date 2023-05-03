// ******************************************************
// * copyright (C) 2023 by rbehm@ibb-aviotec.com
// * File: main.cpp
// * created 2023-05-03 with pro-config V0.2
// ******************************************************

//#include "config.h"

static QString findPort();

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	app.setApplicationName("obls-pv");
	app.setApplicationVersion("V0.1");
	app.setOrganizationDomain("ibb-aviotec.com");
	app.setOrganizationName("IBB-aviotech");
//	QString fileName;
	{
		QCommandLineParser parser;
		parser.setApplicationDescription("Frontend for PulseView to autoselect  OBLS port");
		parser.addHelpOption();
		parser.addVersionOption();
//		parser.addPositionalArgument("file", "file-name");
		parser.process(app);
//		if (! parser.positionalArguments().isEmpty())
//		{
//			fileName = parser.positionalArguments().first();
//		}
	}
//	{
//		QFile sf(":/styles.css");
//		sf.open(QIODevice::ReadOnly);
//		app.setStyleSheet(sf.readAll());
//	}
//	Config::loadDefaults();
	QString port = findPort();
	if (port.isNull())
	{
		qWarning() << app.applicationName() << "OBLS not found";
		return EXIT_FAILURE;
	}
	QString pvCmd("/usr/bin/pulseview --driver=ols:conn=%1 &");
	pvCmd = pvCmd.arg(port);
	qDebug() << pvCmd << port;
	system(pvCmd.toLocal8Bit());
	return EXIT_SUCCESS;
}

static QString findPort()
{
	const uint16_t vid = 0x04d8;
	const uint16_t pid = 0xfc92;
	foreach (const QSerialPortInfo &pi, QSerialPortInfo::availablePorts())
	{
		if ((pi.vendorIdentifier() == vid) && (pi.productIdentifier()  == pid))
		{
			return pi.systemLocation();
		}
	}
	return QString();
}
