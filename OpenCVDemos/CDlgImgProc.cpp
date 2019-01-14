// CDlgImgProc.cpp : implementation file
//

#include "stdafx.h"
#include "OpenCVDemos.h"
#include "CDlgImgProc.h"
#include "afxdialogex.h"


// CDlgImgProc dialog

IMPLEMENT_DYNAMIC(CDlgImgProc, CDialogEx)

CDlgImgProc::CDlgImgProc(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IMGPROC, pParent)
	, m_nImgProcType(-1)
{

}

CDlgImgProc::~CDlgImgProc()
{
}

void CDlgImgProc::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FILTERING, m_comboFilter);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Control(pDX, IDC_COMBO_GEOMETRIC, m_comboGeometric);
	DDX_Control(pDX, IDC_COMBO_MISCELLANCEOUS, m_comboMiscellaneous);
	DDX_Control(pDX, IDC_COMBO_DRAWING, m_comboDrawing);
	DDX_Control(pDX, IDC_COMBO_SUBDIVISION, m_comboSubdivision);
	DDX_Control(pDX, IDC_COMBO_HISTOGRAMS, m_comboHistogram);
	DDX_Control(pDX, IDC_COMBO_FEATURES, m_comboFeature);
}


BEGIN_MESSAGE_MAP(CDlgImgProc, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_FILTERING, &CDlgImgProc::OnCbnSelchangeComboFiltering)
	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_COMBO_GEOMETRIC, &CDlgImgProc::OnCbnSelchangeComboGeometric)
	ON_CBN_SELCHANGE(IDC_COMBO_MISCELLANCEOUS, &CDlgImgProc::OnCbnSelchangeComboMiscellanceous)
	ON_CBN_SELCHANGE(IDC_COMBO_DRAWING, &CDlgImgProc::OnCbnSelchangeComboDrawing)
	ON_CBN_SELCHANGE(IDC_COMBO_SUBDIVISION, &CDlgImgProc::OnCbnSelchangeComboSubdivision)
	ON_CBN_SELCHANGE(IDC_COMBO_HISTOGRAMS, &CDlgImgProc::OnCbnSelchangeComboHistograms)
	ON_CBN_SELCHANGE(IDC_COMBO_FEATURES, &CDlgImgProc::OnCbnSelchangeComboFeatures)
END_MESSAGE_MAP()


// CDlgImgProc message handlers

BOOL CDlgImgProc::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Filtering
	m_comboFilter.AddString(L"bilateralFilter");
	m_comboFilter.AddString(L"boxFilter");
	m_comboFilter.AddString(L"GaussianBlur");
	m_comboFilter.AddString(L"medianBlur");
	m_comboFilter.AddString(L"dilate");
	m_comboFilter.AddString(L"erode");
	m_comboFilter.AddString(L"Laplacian");
	m_comboFilter.AddString(L"pyrDown");
	m_comboFilter.AddString(L"pyrUp");
	m_comboFilter.AddString(L"Scharr");
	m_comboFilter.AddString(L"Sobel");
	// Geometric Image Transformations
	m_comboGeometric.AddString(L"resize");
	m_comboGeometric.AddString(L"warpAffine");
	m_comboGeometric.AddString(L"flip");		// defined in opencv core module
	// Miscellaneous Image Transformations
	m_comboMiscellaneous.AddString(L"adaptiveThreshold");
	m_comboMiscellaneous.AddString(L"floodFill");
	m_comboMiscellaneous.AddString(L"grabCut");
	m_comboMiscellaneous.AddString(L"integral");
	m_comboMiscellaneous.AddString(L"threshold");
	// Drawing
	m_comboDrawing.AddString(L"arrowedLine");
	m_comboDrawing.AddString(L"circle");
	m_comboDrawing.AddString(L"drawContours");
	m_comboDrawing.AddString(L"drawMarker");
	m_comboDrawing.AddString(L"ellipse");
	m_comboDrawing.AddString(L"line");
	m_comboDrawing.AddString(L"polylines");
	m_comboDrawing.AddString(L"putText");
	m_comboDrawing.AddString(L"rectangle");
	// Planar Subdivision
	m_comboSubdivision.AddString(L"getTriangleList");
	m_comboSubdivision.AddString(L"getVoronoiFacetList");
	// Histograms
	m_comboHistogram.AddString(L"calcHist");
	m_comboHistogram.AddString(L"compareHist");
	// Feature Detection
	m_comboFeature.AddString(L"Canny");
	m_comboFeature.AddString(L"cornerEigenValsAndVecs");
	m_comboFeature.AddString(L"createLineSegmentDetector");
	m_comboFeature.AddString(L"HoughCircles");
	m_comboFeature.AddString(L"HoughLines");

	try {
		m_matImg = cv::imread(".\\imgProc.jpg");
	}
	catch (cv::Exception ex) {
		cout << "OnInitDialog" << ex.what() << "__" << __LINE__ << endl;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgImgProc::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnClose();
}


void CDlgImgProc::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (GetDlgItem(IDC_STATIC_IMG) && ::IsWindow(GetDlgItem(IDC_STATIC_IMG)->m_hWnd)) {
		CRect rect(POINT{ 10, 120 }, POINT{ cx - 10, cy - 10 });
		GetDlgItem(IDC_STATIC_IMG)->MoveWindow(&rect);

		m_pDC = GetDlgItem(IDC_STATIC_IMG)->GetDC();
		GetDlgItem(IDC_STATIC_IMG)->GetClientRect(&m_rectImg);
		m_pDC->SetStretchBltMode(COLORONCOLOR);
	}
}

ULONG CDlgImgProc::DrawMatImg(cv::Mat& mat)
{
	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();
	CImage img;
	img.Create(width, height, 8 * channels);
	UCHAR* ps;
	UCHAR* pimg = (UCHAR*)img.GetBits();
	int step = img.GetPitch();
	for (int i = 0; i < height; ++i) {
		ps = (mat.ptr<UCHAR>(i));
		for (int j = 0; j < width; ++j) {
			if (channels == 1) {
				*(pimg + i * step + j) = ps[j];
			}
			else if (channels == 3) {
				for (int k = 0; k < 3; ++k) {
					*(pimg + i * step + j * 3 + k) = ps[j * 3 + k];
				}
			}
		}
	}
	if (1 == channels) {
		RGBQUAD colorTab[256];
		for (int i = 0; i < 256; i++){
			colorTab[i].rgbBlue = colorTab[i].rgbGreen = colorTab[i].rgbRed = i;
		}
		img.SetColorTable(0, 256, colorTab);
	}
	img.Draw(m_pDC->m_hDC, m_rectImg);
	img.Destroy();

	return 0;
}

void CDlgImgProc::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (*pScrollBar == m_slider) {
		SetDlgItemInt(IDC_STATIC_SLIDER_VALUE, m_slider.GetPos());
		switch (m_nImgProcType) {
		case 0:
			OnCbnSelchangeComboFiltering();	break;
		case 1:
			OnCbnSelchangeComboGeometric();	break;
		case 2:
			OnCbnSelchangeComboMiscellanceous();	break;
		case 3:
			OnCbnSelchangeComboDrawing();	break;
		case 4:
			OnCbnSelchangeComboSubdivision();	break;
		case 5:
			OnCbnSelchangeComboHistograms(); break;
		case 6:
			OnCbnSelchangeComboFeatures();	break;
		default:
			break;
		}
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDlgImgProc::OnCbnSelchangeComboFiltering()
{
	m_nImgProcType = 0;
	cv::Mat newMatImg = m_matImg.clone();
	try {
		switch (m_comboFilter.GetCurSel()) {
		case 0:
			m_slider.SetRangeMin(1);
			m_slider.SetRangeMax(31);
			cv::bilateralFilter(m_matImg, newMatImg, m_slider.GetPos(),
				m_slider.GetPos() * 2, m_slider.GetPos() * 2);
			break;
		case 1:
			m_slider.SetRangeMin(1);
			m_slider.SetRangeMax(10);
			cv::boxFilter(m_matImg, newMatImg, -1, cv::Point(m_slider.GetPos(), m_slider.GetPos()));
			break;
		case 2: {
			m_slider.SetRangeMin(3);
			m_slider.SetRangeMax(10);
			int size = (0 == m_slider.GetPos() % 2 ? m_slider.GetPos() + 1 : m_slider.GetPos());
			cv::GaussianBlur(m_matImg, newMatImg, cv::Size(size, size), 0, 0);
		}
				break;
		case 3: {
			m_slider.SetRangeMin(3);
			m_slider.SetRangeMax(10);
			int size = (0 == m_slider.GetPos() % 2 ? m_slider.GetPos() + 1 : m_slider.GetPos());
			cv::medianBlur(m_matImg, newMatImg, size);
		}
				break;
		case 4: {
			m_slider.SetRangeMin(1);
			m_slider.SetRangeMax(10);
			cv::Mat element = cv::getStructuringElement(0,
				cv::Size(2 * m_slider.GetPos() + 1, 2 * m_slider.GetPos() + 1),
				cv::Point(m_slider.GetPos(), m_slider.GetPos()));
			cv::dilate(m_matImg, newMatImg, element);
		}
				break;
		case 5: {
			m_slider.SetRangeMin(1);
			m_slider.SetRangeMax(10);
			cv::Mat element = cv::getStructuringElement(0,
				cv::Size(2 * m_slider.GetPos() + 1, 2 * m_slider.GetPos() + 1),
				cv::Point(m_slider.GetPos(), m_slider.GetPos()));
			cv::erode(m_matImg, newMatImg, element);
		}
				break;
		case 6:
			cv::Laplacian(m_matImg, newMatImg, CV_16S);
			cv::convertScaleAbs(newMatImg, newMatImg);
			break;
		case 7:
			cv::pyrDown(m_matImg, newMatImg);
			break;
		case 8:
			cv::pyrUp(m_matImg, newMatImg);
			break;
		case 9: {
			cv::Mat matX, matY;
			cv::Scharr(m_matImg, matX, CV_16S, 1, 0, 1, 0);
			cv::convertScaleAbs(matX, matX);
			cv::Scharr(m_matImg, matY, CV_16S, 1, 0, 1, 0);
			cv::convertScaleAbs(matY, matY);
			cv::addWeighted(matX, 0.5, matY, 0.5, 0, newMatImg);
		}
				break;
		case 10: {
			cv::Mat matX, matY;
			cv::Sobel(m_matImg, matX, CV_16S, 1, 0, 3, 1, 1);
			cv::convertScaleAbs(matX, matX);
			cv::Sobel(m_matImg, matY, CV_16S, 1, 0, 3, 1, 1);
			cv::convertScaleAbs(matY, matY);
			cv::addWeighted(matX, 0.5, matY, 0.5, 0, newMatImg);
		}
				 break;
		default:
			break;
		}
	}
	catch (cv::Exception ex) {
		cout << "OnCbnSelchangeComboFiltering" << ex.what() << "__" << __LINE__ << endl;
	}

	DrawMatImg(newMatImg);
}

void CDlgImgProc::OnCbnSelchangeComboGeometric()
{
	m_nImgProcType = 1;
	cv::Mat newMatImg = m_matImg.clone();
	try {
		switch (m_comboGeometric.GetCurSel()) {
		case 0:
			m_slider.SetRangeMin(1);
			m_slider.SetRangeMax(10);
			cv::resize(m_matImg, newMatImg, 
				cv::Size(m_matImg.cols * m_slider.GetPos() / 10, m_matImg.rows * m_slider.GetPos() / 10));
			break;
		case 1: {
				m_slider.SetRangeMin(1);
				m_slider.SetRangeMax(360);
				cv::Point2f centerPoint(float(m_matImg.cols / 2), float(m_matImg.rows / 2.0));
				cv::Mat m = cv::getRotationMatrix2D(centerPoint, double(m_slider.GetPos()), 1.0);
				cv::warpAffine(m_matImg, newMatImg, m, cv::Size(m_matImg.cols, m_matImg.rows));
			}
			break;
		case 2:
			m_slider.SetRangeMin(-1);
			m_slider.SetRangeMax(1);
			cv::flip(m_matImg, newMatImg, m_slider.GetPos());
			break;
		default:
			break;
		}
	}
	catch (cv::Exception ex) {
		cout << "OnCbnSelchangeComboGeometric" << ex.what() << "__" << __LINE__ << endl;
	}

	DrawMatImg(newMatImg);
}

void CDlgImgProc::OnCbnSelchangeComboMiscellanceous()
{
	m_nImgProcType = 2;
	cv::Mat newMatImg = m_matImg.clone();
	try {
		switch (m_comboMiscellaneous.GetCurSel()) {
		case 0:
			m_slider.SetRangeMin(3);
			m_slider.SetRangeMax(31);
			cv::cvtColor(m_matImg, newMatImg, cv::COLOR_BGR2GRAY);
			cv::adaptiveThreshold(newMatImg, newMatImg, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY,
				(0 == m_slider.GetPos() % 2 ? m_slider.GetPos() + 1 : m_slider.GetPos()), 10);
			break;
		case 1: {
				m_slider.SetRangeMin(0);
				m_slider.SetRangeMax(newMatImg.rows - 1);
				int b = (unsigned)cv::theRNG() & 255;
				int g = (unsigned)cv::theRNG() & 255;
				int r = (unsigned)cv::theRNG() & 255;
				cv::Rect ccomp;
				cv::Scalar newVal = cvScalar(b, g, r);
				cv::floodFill(newMatImg, cv::Point(m_slider.GetPos(), m_slider.GetPos()), newVal, &ccomp, cv::Scalar(20, 20, 20),
					cv::Scalar(20, 20, 20));
			}
			break;
		case 2:{
				m_slider.SetRangeMin(0);
				m_slider.SetRangeMax(newMatImg.rows / 2);
				cv::Mat mask, bgdModel, fgdModel;
				cv::Rect rect(newMatImg.cols / 2 - m_slider.GetPos(), newMatImg.rows / 2 - m_slider.GetPos(),
					newMatImg.cols - 2 * m_slider.GetPos(), newMatImg.rows - 2 * m_slider.GetPos());
				rect = cv::Rect(100, 100, 300, 300);
				cv::grabCut(newMatImg, mask, rect, bgdModel, fgdModel, 1, cv::GC_INIT_WITH_RECT);
				cv::compare(mask, cv::GC_PR_FGD, mask, cv::CMP_EQ);
				cv::Mat foreground(newMatImg.size(), CV_8UC3, cv::Scalar(255, 255, 255));
				newMatImg.copyTo(foreground, mask);
				newMatImg = foreground;
			}
			break;
		case 3:
			cv::integral(m_matImg, newMatImg, CV_32F);
			cv::normalize(newMatImg, newMatImg, 0, 255, cv::NORM_MINMAX);
			cv::convertScaleAbs(newMatImg, newMatImg);
			break;
		case 4:
			m_slider.SetRangeMin(0);
			m_slider.SetRangeMax(255);
			cv::cvtColor(m_matImg, newMatImg, cv::COLOR_BGR2GRAY);
			cv::threshold(newMatImg, newMatImg, m_slider.GetPos(), 255, cv::THRESH_BINARY);
			break;
		default:
			break;
		}
	}
	catch (cv::Exception ex) {
		cout << "OnCbnSelchangeComboGeometric" << ex.what() << "__" << __LINE__ << endl;
	}

	DrawMatImg(newMatImg);
}

void CDlgImgProc::OnCbnSelchangeComboDrawing()
{
	m_nImgProcType = 3;
	cv::Mat newMatImg = m_matImg.clone();
	try {
		switch (m_comboDrawing.GetCurSel()) {
		case 0:
			cv::arrowedLine(newMatImg, cv::Point(100, 100), cv::Point(200, 200), cv::Scalar(0, 0, 255), 5);
			break;
		case 1: 
			cv::circle(newMatImg, cv::Point(300, 400), 50, cv::Scalar(255, 0, 0), 5);
			break;
		case 2: {
				cv::Mat tmp;
				cv::cvtColor(newMatImg, tmp, cv::COLOR_BGR2GRAY);
				std::vector<std::vector<cv::Point>> contours;
				std::vector<cv::Vec4i> hierarchy;
				cv::findContours(tmp, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
				for (UINT idx = 0; idx < hierarchy.size(); idx++) {
					cv::Scalar color(rand() & 255, rand() & 255, rand() & 255);
					cv::drawContours(newMatImg, contours, idx, color, cv::LINE_4, 8, hierarchy);
				}
			}
			break;
		case 3:
			cv::drawMarker(newMatImg, cv::Point(300, 400), cv::Scalar(0, 255, 0));
			break;
		case 4:
			m_slider.SetRangeMin(0);
			m_slider.SetRangeMax(180);
			cv::ellipse(newMatImg, cv::Point(300, 400), cv::Size(100, 40), m_slider.GetPos(), 
				m_slider.GetPos() - 100, m_slider.GetPos() + 200, cv::Scalar(255, 0, 0), 5);
			break;
		case 5:
			cv::line(newMatImg, cv::Point(100, 200), cv::Point(200, 100), cv::Scalar(255, 0, 0), 5);
			break;
		case 6: {
				cv::Point* points[] = { &cv::Point(250, 270), &cv::Point(550, 170), &cv::Point(670, 380),
					&cv::Point(640, 450), &cv::Point(550, 450), &cv::Point(370, 280) };
				int npts = 5;
				cv::Point pt[][5] = { {cv::Point(250, 270), cv::Point(550, 170), cv::Point(670, 380), cv::Point(640, 450), cv::Point(370, 280)},
					{cv::Point(250, 270), cv::Point(550, 170), cv::Point(670, 380), cv::Point(640, 450), cv::Point(370, 280)} };
				const cv::Point* ppt[] = { pt[0], pt[1] };
				int npt[] = { 5, 5 };
				cv::polylines(newMatImg, ppt, npt, 2, true, cv::Scalar(255, 0, 0), 5);
			}
			break;
		case 7:
			cv::putText(newMatImg, "putText", cv::Point(200, 200), cv::FONT_HERSHEY_SIMPLEX, 5.0, cv::Scalar(255, 0, 0));
			break;
		case 8:
			cv::rectangle(newMatImg, cv::Rect(200, 200, 200, 100), cv::Scalar(255, 0, 0), 5);
			break;
		default:
			break;
		}
	}
	catch (cv::Exception ex) {
		cout << "OnCbnSelchangeComboDrawing" << ex.what() << "__" << __LINE__ << endl;
	}

	DrawMatImg(newMatImg);
}

void CDlgImgProc::OnCbnSelchangeComboSubdivision()
{
	m_nImgProcType = 4;
	cv::Mat newMatImg = m_matImg.clone();
	std::vector<cv::Point2f> points;
	points.push_back(cv::Point2f(549, 176));
	points.push_back(cv::Point2f(460, 188));
	points.push_back(cv::Point2f(544, 189));
	points.push_back(cv::Point2f(365, 205));
	points.push_back(cv::Point2f(558, 212));
	points.push_back(cv::Point2f(578, 210));
	points.push_back(cv::Point2f(592, 225));
	points.push_back(cv::Point2f(368, 232));
	points.push_back(cv::Point2f(611, 241));
	points.push_back(cv::Point2f(343, 256));
	points.push_back(cv::Point2f(407, 252));
	points.push_back(cv::Point2f(471, 263));
	points.push_back(cv::Point2f(518, 273));
	points.push_back(cv::Point2f(575, 247));
	points.push_back(cv::Point2f(596, 249));
	points.push_back(cv::Point2f(382, 284));
	points.push_back(cv::Point2f(597, 283));
	points.push_back(cv::Point2f(318, 292));
	points.push_back(cv::Point2f(318, 292));
	points.push_back(cv::Point2f(293, 303));
	points.push_back(cv::Point2f(337, 308));
	points.push_back(cv::Point2f(308, 326));
	points.push_back(cv::Point2f(559, 317));
	points.push_back(cv::Point2f(620, 318));
	points.push_back(cv::Point2f(650, 336));
	points.push_back(cv::Point2f(667, 380));
	points.push_back(cv::Point2f(630, 394));
	points.push_back(cv::Point2f(559, 402));
	points.push_back(cv::Point2f(615, 418));
	points.push_back(cv::Point2f(600, 441));
	points.push_back(cv::Point2f(557, 453));
	points.push_back(cv::Point2f(600, 461));
	points.push_back(cv::Point2f(620, 460));
	points.push_back(cv::Point2f(650, 450));
	cv::Rect rect(0, 0, newMatImg.cols, newMatImg.rows);
	cv::Subdiv2D subdiv(rect);
	subdiv.insert(points);

	try {
		switch (m_comboSubdivision.GetCurSel()) {
		case 0: {
				std::vector<cv::Vec6f> triangleList;
				subdiv.getTriangleList(triangleList);
				std::vector<cv::Point> pt(3);
				for (UINT i = 0; i < triangleList.size(); i++){
					cv::Vec6f t = triangleList[i];
					pt[0] = cv::Point(cvRound(t[0]), cvRound(t[1]));
					pt[1] = cv::Point(cvRound(t[2]), cvRound(t[3]));
					pt[2] = cv::Point(cvRound(t[4]), cvRound(t[5]));
					if (rect.contains(pt[0]) && rect.contains(pt[1]) && rect.contains(pt[2])){
						line(newMatImg, pt[0], pt[1], cv::Scalar(0, 255, 0), 2);
						line(newMatImg, pt[1], pt[2], cv::Scalar(0, 255, 0), 2);
						line(newMatImg, pt[2], pt[0], cv::Scalar(0, 255, 0), 2);
					}
				}
			}
			break;
		case 1:{
				std::vector<std::vector<cv::Point2f> > facets;
				std::vector<cv::Point2f> centers;
				subdiv.getVoronoiFacetList(std::vector<int>(), facets, centers);
				std::vector<cv::Point> ifacet;
				std::vector<std::vector<cv::Point>> ifacets(1);
				for (size_t i = 0; i < facets.size(); i++){
					ifacet.resize(facets[i].size());
					for (size_t j = 0; j < facets[i].size(); j++) {
						ifacet[j] = facets[i][j];
					}
					cv::fillConvexPoly(newMatImg, ifacet, cv::Scalar(rand() & 255, rand() & 255, rand() & 255), 8, 0);
					ifacets[0] = ifacet;
					cv::polylines(newMatImg, ifacets, true, cv::Scalar(), 1, CV_AA, 0);
					cv::circle(newMatImg, centers[i], 3, cv::Scalar(), CV_FILLED, CV_AA, 0);
				}
			}
			break;
		default:
			break;
		}
	}
	catch (cv::Exception ex) {
		cout << "OnCbnSelchangeComboSubdivision" << ex.what() << "__" << __LINE__ << endl;
	}

	DrawMatImg(newMatImg);
}

void CDlgImgProc::OnCbnSelchangeComboHistograms()
{
	m_nImgProcType = 5;
	cv::Mat newMatImg = m_matImg.clone();
	try {
		switch (m_comboHistogram.GetCurSel()) {
		case 0: {
				m_slider.SetRangeMin(0);
				m_slider.SetRangeMax(2);
				cv::Mat matSplit[3];
				cv::split(newMatImg, matSplit);
				int channels[] = { 0 };
				int histSize[] = { 256 };
				float histRange[] = { 0, 256 };
				const float* ranges[] = { histRange };
				cv::Mat matHist;
				cv::calcHist(&matSplit[m_slider.GetPos()], 1, channels, cv::Mat(), matHist, 1, histSize, ranges, true, false);
				int scale = 1;
				cv::Mat histPic(histSize[0] * scale, histSize[0], CV_8U, cv::Scalar(255));
				double maxValue = 0;
				double minValue = 0;
				cv::minMaxLoc(matHist, &minValue, &maxValue, NULL, NULL);
				double rate = (histSize[0] / maxValue)*0.9;
				for (int i = 0; i < histSize[0]; i++){
					float value = matHist.at<float>(i);
					cv::line(histPic, cv::Point(i*scale, histSize[0]), cv::Point(i*scale, (int)(histSize[0] - value * rate)), cv::Scalar(0,0,0));
				}
				newMatImg = histPic;
			}
			break;
		case 1: {
				cv::Mat matSplit[3];
				cv::split(newMatImg, matSplit);
				int channels[] = { 0 };
				int histSize[] = { 256 };
				float histRange[] = { 0, 256 };
				const float* ranges[] = { histRange };
				cv::Mat matHistB, matHistG;
				cv::calcHist(&matSplit[0], 1, channels, cv::Mat(), matHistB, 1, histSize, ranges, true, false);
				cv::calcHist(&matSplit[1], 1, channels, cv::Mat(), matHistG, 1, histSize, ranges, true, false);
				double score = cv::compareHist(matHistB, matHistG, cv::HISTCMP_CORREL);
				WCHAR strScore[32] = { 0 };
				swprintf_s(strScore, L"%f", score);
				::MessageBoxW(nullptr, strScore, L"compareHist", 0);
			}
			break;
		default:
			break;
		}
	}
	catch (cv::Exception ex) {
		cout << "OnCbnSelchangeComboHistograms:" << ex.what() << "__" << __LINE__ << endl;
	}

	DrawMatImg(newMatImg);
}


void CDlgImgProc::OnCbnSelchangeComboFeatures()
{
	m_nImgProcType = 6;
	cv::Mat newMatImg = m_matImg.clone();
	try {
		switch (m_comboFeature.GetCurSel()) {
		case 0: 
			cv::cvtColor(newMatImg, newMatImg, cv::COLOR_BGR2GRAY);
			m_slider.SetRangeMin(0);
			m_slider.SetRangeMax(255);
			cv::Canny(newMatImg, newMatImg, 0, m_slider.GetPos(), 5);
			break;
		case 1: 
			cv::cvtColor(newMatImg, newMatImg, cv::COLOR_BGR2GRAY);
			m_slider.SetRangeMin(1);
			m_slider.SetRangeMax(255);
			cv::cornerEigenValsAndVecs(newMatImg, newMatImg, m_slider.GetPos(), 5);
			break;
		case 2: {
				cv::cvtColor(newMatImg, newMatImg, cv::COLOR_BGR2GRAY);
				cv::Ptr<cv::LineSegmentDetector> ls = cv::createLineSegmentDetector(cv::LSD_REFINE_STD);
				std::vector<cv::Vec4f> lines_std;
				ls->detect(newMatImg, lines_std);
				ls->drawSegments(newMatImg, lines_std);
			}
			break;
		case 3: {
				cv::Mat gray;
				cv::cvtColor(newMatImg, gray, cv::COLOR_BGR2GRAY);
				cv::GaussianBlur(gray, gray, cv::Size(3, 3), 2, 2);
				std::vector<cv::Vec3f> circles;
				cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 2, gray.rows / 4, 200, 100);
				for (size_t i = 0; i < circles.size(); i++) {
					cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
					int radius = cvRound(circles[i][2]);
					cv::circle(newMatImg, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
					cv::circle(newMatImg, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
				}
			}
			break;
		case 4: {
				cv::Mat bin;
				cv::cvtColor(newMatImg, bin, cv::COLOR_BGR2GRAY);
				cv::Canny(bin, bin, 50, 200, 3);
				//cv::cvtColor(newMatImg, newMatImg, cv::COLOR_GRAY2BGR);
				std::vector<cv::Vec2f> lines;
				cv::HoughLines(bin, lines, 1, CV_PI / 180, 150, 0, 0);
				for (size_t i = 0; i < lines.size(); i++){
					float rho = lines[i][0], theta = lines[i][1];
					cv::Point pt1, pt2;
					double a = cos(theta), b = sin(theta);
					double x0 = a * rho, y0 = b * rho;
					pt1.x = cvRound(x0 + 1000 * (-b));
					pt1.y = cvRound(y0 + 1000 * (a));
					pt2.x = cvRound(x0 - 1000 * (-b));
					pt2.y = cvRound(y0 - 1000 * (a));
					line(newMatImg, pt1, pt2, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
				}
			}
			break;
		default:
			break;
		}
	}
	catch (cv::Exception ex) {
		cout << "OnCbnSelchangeComboFeatures:" << ex.what() << "__" << __LINE__ << endl;
	}

	DrawMatImg(newMatImg);
}
