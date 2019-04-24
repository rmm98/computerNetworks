BEGIN{
	tcp_count = 0;
	udp_count = 0;
}

{
	packetType = $5;
	if(packetType == "tcp")
	{
		tcp_count++;
	}
	else if(packetType == "cbr")
	{
		udp_count++;
	}
}

END{
	printf("TCP packets = %d\nUDP packets = %d\n",tcp_count,udp_count);
}
