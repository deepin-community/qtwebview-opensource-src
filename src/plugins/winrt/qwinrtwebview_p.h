/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtWebView module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QWINRTWEBVIEW_P_H
#define QWINRTWEBVIEW_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <private/qabstractwebview_p.h>

namespace ABI {
    namespace Windows {
        namespace UI {
            namespace Xaml {
                namespace Controls {
                    struct IWebView;
                    struct IWebViewNavigationStartingEventArgs;
                    struct IWebViewNavigationCompletedEventArgs;
                    struct IWebViewUnviewableContentIdentifiedEventArgs;
                }
            }
        }
    }
}

QT_BEGIN_NAMESPACE

struct WinRTWebView;
class QWinRTWebViewPrivate : public QAbstractWebView
{
    Q_OBJECT
public:
    explicit QWinRTWebViewPrivate(QObject *parent = nullptr);
    ~QWinRTWebViewPrivate() Q_DECL_OVERRIDE;

    QString httpUserAgent() const Q_DECL_OVERRIDE;
    void setHttpUserAgent(const QString &userAgent) Q_DECL_OVERRIDE;
    QUrl url() const Q_DECL_OVERRIDE;
    void setUrl(const QUrl &url) Q_DECL_OVERRIDE;
    bool canGoBack() const Q_DECL_OVERRIDE;
    bool canGoForward() const Q_DECL_OVERRIDE;
    QString title() const Q_DECL_OVERRIDE;
    int loadProgress() const Q_DECL_OVERRIDE;
    bool isLoading() const Q_DECL_OVERRIDE;

    void setParentView(QObject *view) Q_DECL_OVERRIDE;
    QObject *parentView() const Q_DECL_OVERRIDE;
    void setGeometry(const QRect &geometry) Q_DECL_OVERRIDE;
    void setVisibility(QWindow::Visibility visibility) Q_DECL_OVERRIDE;
    void setVisible(bool visible) Q_DECL_OVERRIDE;

public Q_SLOTS:
    void goBack() Q_DECL_OVERRIDE;
    void goForward() Q_DECL_OVERRIDE;
    void reload() Q_DECL_OVERRIDE;
    void stop() Q_DECL_OVERRIDE;
    void loadHtml(const QString &html, const QUrl &baseUrl = QUrl()) Q_DECL_OVERRIDE;

protected:
    void runJavaScriptPrivate(const QString &script, int callbackId) Q_DECL_OVERRIDE;

private:
    HRESULT onNavigationStarted(ABI::Windows::UI::Xaml::Controls::IWebView *, ABI::Windows::UI::Xaml::Controls::IWebViewNavigationStartingEventArgs *);
    HRESULT onNavigationCompleted(ABI::Windows::UI::Xaml::Controls::IWebView *, ABI::Windows::UI::Xaml::Controls::IWebViewNavigationCompletedEventArgs *);
    HRESULT onUnviewableContent(ABI::Windows::UI::Xaml::Controls::IWebView *,
                             ABI::Windows::UI::Xaml::Controls::IWebViewUnviewableContentIdentifiedEventArgs *);
    QScopedPointer<WinRTWebView> d;
};

QT_END_NAMESPACE

#endif // QWINRTWEBVIEW_P_H
