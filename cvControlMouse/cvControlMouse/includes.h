extern CvCapture* cvSetCamera(char* Window_name="avi",int index=0);
extern IplImage *cvGetCamera(CvCapture* capture);
extern CvPoint* Calculate_img(IplImage * src_img);
extern int BrightestPoint(IplImage * img);