///////////////////////////////////////////////////////////////////////////////
// Name:        tests/controls/webtest.cpp
// Purpose:     wxWebView unit test
// Author:      Steven Lamerton
// Created:     2011-07-08
// RCS-ID:      $Id$
// Copyright:   (c) 2011 Steven Lamerton
///////////////////////////////////////////////////////////////////////////////

#include "testprec.h"

#if wxUSE_WEB

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/app.h"
#endif // WX_PRECOMP

#include "testableframe.h"
#include "wx/uiaction.h"
#include "wx/webview.h"
#include "asserthelper.h"

class WebTestCase : public CppUnit::TestCase
{
public:
    WebTestCase() { }

    void setUp();
    void tearDown();

private:
    CPPUNIT_TEST_SUITE( WebTestCase );
        CPPUNIT_TEST( Title );
    CPPUNIT_TEST_SUITE_END();

    void Title();

    wxWebView* m_browser;

    DECLARE_NO_COPY_CLASS(WebTestCase)
};

// register in the unnamed registry so that these tests are run by default
CPPUNIT_TEST_SUITE_REGISTRATION( WebTestCase );

// also include in its own registry so that these tests can be run alone
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( WebTestCase, "WebTestCase" );

void WebTestCase::setUp()
{
    m_browser = wxWebView::New(wxTheApp->GetTopWindow(), wxID_ANY);
}

void WebTestCase::tearDown()
{
    wxDELETE(m_browser);
}

void WebTestCase::Title()
{
    CPPUNIT_ASSERT_EQUAL("", m_browser->GetCurrentTitle());

    //Test title after loading raw html
    m_browser->SetPage("<html><title>Title</title></html>", "");
    CPPUNIT_ASSERT_EQUAL("Title", m_browser->GetCurrentTitle());

    //Test title after loading a url, we yield to let events process
    m_browser->LoadUrl("about:blank");
    wxYield();
    CPPUNIT_ASSERT_EQUAL("", m_browser->GetCurrentTitle());
}

#endif //wxUSE_WEB