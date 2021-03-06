//Export selected asset history to CSV

#define SPOT_SYMBOL0	"BTCUSD"		// original zorro btc data
#define INDEX_SYMBOL	"BTC-USD"		// okex underlying USD index data, 24h hitory avail
#define EXCH_SYMBOL2	"USDT-USD"		// okex underlying USDT index data, 24h hitory avail
#define SPOT_SYMBOL	"BTC-USDT"		// okex spot, full hitory avail
#define SWAP_SYMBOL	"BTC-USD-SWAP"	// okex perp swap, full hitory avail

function run()
{
	StartDate = 20210101;
	EndDate = 20211231;
	LookBack = 0;
	BarPeriod = 1;

	bool highPrecisionAssetType = false;
	// asset(SPOT_SYMBOL0);
	asset(INDEX_SYMBOL);
	// asset(EXCH_SYMBOL2); highPrecisionAssetType = true;
	// asset(SPOT_SYMBOL);
	// asset(SWAP_SYMBOL);
	
	string Format = ifelse(highPrecisionAssetType || assetType(Asset) == FOREX,
		"\n%04i-%02i-%02i %02i:%02i, %.5f, %.5f, %.5f, %.5f",
		"\n%04i-%02i-%02i %02i:%02i, %.1f, %.1f, %.1f, %.1f");
	char FileName[40];
	sprintf(FileName,"History\\%s.csv",strx(Asset,"/","")); // remove slash from forex pairs
	
	if(is(INITRUN))
		file_write(FileName,"Date,Open,High,Low,Close",0);
	else
		file_append(FileName,strf(Format,
			year(),month(),day(),hour(),minute(),
			round(priceOpen(),0.1*PIP),
			round(priceHigh(),0.1*PIP),
			round(priceLow(),0.1*PIP),
			round(priceClose(),0.1*PIP)));
}

// To generate a XTS object in R from the exported data:
// Data <- xts(read.zoo("MyAsset.csv",tz="UTC",format="%Y-%m-%d %H:%M",sep=",",header=TRUE))
