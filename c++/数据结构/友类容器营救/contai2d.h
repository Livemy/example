class Rescue
{
public:
	Rescue(double fMin,double fMax,
		double fCriticalDistance);
	~Rescue();
	void initRescue();
	Logical searchMore();
	void getCoords();
	double getDistance()
	{return m_pDistance->getDistance();}

protected:
	double m_fMin;
	double m_fMax;
	double m_fShift;
	double m_fCriticalDistance;
	Distance *m_pDistance;
	Random *m_pRandom;

	double calcRandCoord()
	{return m_pRandom->getRandom() * m_fMax + m_fMin;}
	double calcRandShift()
	{return(0.5-m_pRandom->getRandom())*m_fShift;}
	double checkCoord(double fX)
	{return(fX>=m_fMin&&fX<=m_fMax)?
         fX:m_fMin+m_fMax/2.;}
};

Rescue::Rescue(double fMin,double fMax,double fCriticalDistance)
{
	m_fMin=fMin;
	m_fMax=fMax;
	m_fShift=(fMax-fMin+1)/10.;
	m_fCriticalDistance=fCriticalDistance;
	m_pDistance=new Distance(0,0,0,0);
	m_pRandom=new Random;
	initRescue();
}

Rescue::~Rescue()
{
	delete m_pDistance;
	delete m_pRandom;
}

void Rescue::initRescue()
{
	double fX=calcRandCoord();
	double fY=calcRandCoord();

	m_pDistance->setPoint1((m_fMin+m_fMax)/2,(m_fMin+m_fMax)/2);
	m_pDistance->setPoint2(fX,fY);
}

Logical Rescue::searchMore()
{
    if(fabs(m_pDistance->m_fDeltaX)<1.0||
		fabs(m_pDistance->m_fDeltaY)<1.0||
		m_pDistance->getDistance()<m_fCriticalDistance)
		return FALSE;
	else
		return TRUE;
}

void Rescue::getCoords()
{
    int fX,fY;
	cout << " Current distance = "
		<< m_pDistance->getDistance() << " \n"
		<< " Current angle = "
		<< m_pDistance->getAngle() << " degrees\n ";

	    /*m_pDistance->m_fDeltaX=calcRandShift();
		m_pDistance->m_fDeltaY=calcRandShift();
		m_pDistance->setPoint2(checkCoord(m_pDistance->m_fX2+
			m_pDistance->m_fDeltaX),
			checkCoord(m_pDistance->m_fY2+m_pDistance->m_fDeltaY));*/

        cout << "Enter movement in X direction : ";
        cin >> fX;
        m_pDistance->m_fDeltaX=fX;
		if(m_pDistance->m_fDeltaX > m_fShift)
			m_pDistance->m_fDeltaX=m_fShift;
		cout << " Enter movement in Y direction : ";
		cin >> fY;
		m_pDistance->m_fDeltaY=fY;
		if(m_pDistance->m_fDeltaY > m_fShift)
			m_pDistance->m_fDeltaY=m_fShift;
		m_pDistance->setPoint1(
			checkCoord(m_pDistance->m_fX1+
			m_pDistance->m_fDeltaX),
			checkCoord(m_pDistance->m_fY1+
			m_pDistance->m_fDeltaY));
}