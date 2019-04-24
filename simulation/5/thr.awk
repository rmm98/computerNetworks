BEGIN{
	sSize = 0;
	throughput = 0;
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
	
	throughput = (sSize/(stopTime-startTime))*(8/1000);
	printf("%f\t%f\n",time,throughput);
	print time , throughput >> "demo.tr"
}

END{
	
}
