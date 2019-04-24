BEGIN{
	sSize = 0;
	tput = 0;
	startTime = 5.0;
	stopTime = 0.1;
}

{
	event = $1;
	time = $2;
	size = $6;
	if(event == "+")
	{
		if(time < startTime)
		{
			startTime = time;
		}
	}
	if(event == "r")
	{
		if(time > stopTime)
		{
			stopTime = time;
		}
		sSize += size;
	}
	tput = (sSize/(stopTime-startTime))*(8/1000);
	printf("%f\t%f\n",time,tput);
	print time , tput >> "demo.tr";
}

END{
	
}
