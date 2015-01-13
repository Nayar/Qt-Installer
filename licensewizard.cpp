/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "licensewizard.h"
#include "functions.h"

LicenseWizard::LicenseWizard(QWidget *parent)
    : QWizard(parent)
{
    setPage(Page_Intro, new IntroPage);
    setPage(Page_Evaluate, new EvaluatePage);
    setPage(Page_Register, new RegisterPage);
    setPage(Page_Details, new DetailsPage);
    setPage(Page_Conclusion, new ConclusionPage);

    setStartId(Page_Intro);

#ifndef Q_OS_MAC
    setWizardStyle(ModernStyle);
#endif

    setOption(HaveHelpButton, true);

    setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));

    connect(this, SIGNAL(helpRequested()), this, SLOT(showHelp()));


    setWindowTitle(tr("Java App Installer"));
}



void LicenseWizard::showHelp()

{
    static QString lastHelpMessage;

    QString message;

    switch (currentId()) {
    case Page_Intro:
        message = tr("");
        break;

    case Page_Evaluate:
        message = tr("Make sure to provide a valid email address, such as "
                     "toni.buddenbrook@example.de.");
        break;
    case Page_Register:
        message = tr("If you don't provide an upgrade key, you will be "
                     "asked to fill in your details.");
        break;
    case Page_Details:
        message = tr("Make sure to provide a valid email address, such as "
                     "thomas.gradgrind@example.co.uk.");
        break;
    case Page_Conclusion:
        message = tr("You must accept the terms and conditions of the "
                     "license to proceed.");
        break;

    default:
        message = tr("This help is likely not to be of any help.");
    }


    if (lastHelpMessage == message)
        message = tr("Sorry, I already gave what help I could. "
                     "Maybe you should try asking a human?");


    QMessageBox::information(this, tr("License Wizard Help"), message);


    lastHelpMessage = message;

}



IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

    topLabel = new QLabel(tr("This wizard will help you register and install your copy of "
                             "<i>Super Product One</i>&trade;"));
    topLabel->setWordWrap(true);

    QLabel *javaEnabled = new QLabel();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topLabel);
    layout->addSpacerItem(new QSpacerItem(10,10));
    layout->addWidget(javaEnabled);
    if(isJavaInstalled()){
        javaEnabled->setText("Java has been detected on your system :)");
    }else{
         javaEnabled->setText("Java is NOT installed on your system.");
         QCheckBox *downloadJavaCheckbox = new QCheckBox("Download Java");
         layout->addWidget(downloadJavaCheckbox);
         registerField("install.java",downloadJavaCheckbox);
         downloadJavaCheckbox->setChecked(true);
    }
    layout->addSpacerItem(new QSpacerItem(10,10));

    setLayout(layout);
}



int IntroPage::nextId() const
{
    return LicenseWizard::Page_Register;
}

bool IntroPage::validatePage()
{
    if(isJavaInstalled())
        return true;
    if(field("install.java").toString() == "true")
        QDesktopServices::openUrl(QUrl("https://java.com/en/download/manual.jsp"));
    return false;
}



EvaluatePage::EvaluatePage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Evaluate <i>Super Product One</i>&trade;"));
    setSubTitle(tr("Please fill both fields. Make sure to provide a valid "
                   "email address (e.g., john.smith@example.com)."));

    nameLabel = new QLabel(tr("N&ame:"));
    nameLineEdit = new QLineEdit;

    nameLabel->setBuddy(nameLineEdit);

    emailLabel = new QLabel(tr("&Email address:"));
    emailLineEdit = new QLineEdit;
    emailLineEdit->setValidator(new QRegExpValidator(QRegExp(".*@.*"), this));
    emailLabel->setBuddy(emailLineEdit);


    registerField("evaluate.name*", nameLineEdit);
    registerField("evaluate.email*", emailLineEdit);


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameLineEdit, 0, 1);
    layout->addWidget(emailLabel, 1, 0);
    layout->addWidget(emailLineEdit, 1, 1);
    setLayout(layout);

}



int EvaluatePage::nextId() const
{
    return LicenseWizard::Page_Conclusion;
}


RegisterPage::RegisterPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Register Your Copy of <i>Super Product One</i>&trade;"));
    setSubTitle(tr("Enter your secret key"));

    nameLabel = new QLabel(tr("N&ame:"));
    nameLineEdit = new QLineEdit;
    nameLabel->setBuddy(nameLineEdit);

   keyLabel = new QLabel(tr("&Key:"));
   keyLineEdit = new QLineEdit;
   keyLabel->setBuddy(keyLineEdit);

    registerField("register.name*", nameLineEdit);
    registerField("register.key*",keyLineEdit);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameLineEdit, 0, 1);
    layout->addWidget(keyLabel, 1, 0);
    layout->addWidget(keyLineEdit, 1, 1);
    setLayout(layout);
}

int RegisterPage::nextId() const
{
    if (keyLineEdit->text().isEmpty()) {
        return LicenseWizard::Page_Details;
    } else {
        return LicenseWizard::Page_Conclusion;
    }
}

bool RegisterPage::validatePage()
{
    if (keyLineEdit->text().isEmpty()) {
        keyLineEdit->setText("fill");
        return false;
    }
    return true;
}


DetailsPage::DetailsPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Fill In Your Details"));
    setSubTitle(tr("Please fill all three fields. Make sure to provide a valid "
                   "email address (e.g., tanaka.aya@example.co.jp)."));

    companyLabel = new QLabel(tr("&Company name:"));
    companyLineEdit = new QLineEdit;
    companyLabel->setBuddy(companyLineEdit);

    emailLabel = new QLabel(tr("&Email address:"));
    emailLineEdit = new QLineEdit;
    emailLineEdit->setValidator(new QRegExpValidator(QRegExp(".*@.*"), this));
    emailLabel->setBuddy(emailLineEdit);

    postalLabel = new QLabel(tr("&Postal address:"));
    postalLineEdit = new QLineEdit;
    postalLabel->setBuddy(postalLineEdit);

    registerField("details.company*", companyLineEdit);
    registerField("details.email*", emailLineEdit);
    registerField("details.postal*", postalLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(companyLabel, 0, 0);
    layout->addWidget(companyLineEdit, 0, 1);
    layout->addWidget(emailLabel, 1, 0);
    layout->addWidget(emailLineEdit, 1, 1);
    layout->addWidget(postalLabel, 2, 0);
    layout->addWidget(postalLineEdit, 2, 1);
    setLayout(layout);
}


int DetailsPage::nextId() const
{
    return LicenseWizard::Page_Conclusion;
}


ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Complete Your Registration"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

    bottomLabel = new QLabel;
    bottomLabel->setWordWrap(true);

    agreeCheckBox = new QCheckBox(tr("I agree to the terms of the license"));

    registerField("conclusion.agree*", agreeCheckBox);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(bottomLabel);
    layout->addWidget(agreeCheckBox);
    setLayout(layout);
}


int ConclusionPage::nextId() const
{
    return -1;
}



void ConclusionPage::initializePage()
{
    QString licenseText;

    if (wizard()->hasVisitedPage(LicenseWizard::Page_Evaluate)) {
        licenseText = tr("<u>Evaluation License Agreement:</u> "
                         "You can use this software for 30 days and make one "
                         "backup, but you are not allowed to distribute it.");
    } else if (wizard()->hasVisitedPage(LicenseWizard::Page_Details)) {
        licenseText = tr("<u>First-Time License Agreement:</u> "
                         "You can use this software subject to the license "
                         "you will receive by email.");
    } else {
        licenseText = tr("<u>Upgrade License Agreement:</u> "
                         "This software is licensed under the terms of your "
                         "current license.");
    }
    bottomLabel->setText(licenseText);
}



void ConclusionPage::setVisible(bool visible)
{
    QWizardPage::setVisible(visible);

    if (visible) {

        wizard()->setButtonText(QWizard::CustomButton1, tr("&Print"));
        wizard()->setOption(QWizard::HaveCustomButton1, true);
        connect(wizard(), SIGNAL(customButtonClicked(int)),
                this, SLOT(printButtonClicked()));

    } else {
        wizard()->setOption(QWizard::HaveCustomButton1, false);
        disconnect(wizard(), SIGNAL(customButtonClicked(int)),
                   this, SLOT(printButtonClicked()));
    }
}


void ConclusionPage::printButtonClicked()
{
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)

#endif
}


DownloadJavaPage::DownloadJavaPage(QWidget *parent)
{
    dm = new DownloadManager();
    dm->append(QUrl(""));
}
