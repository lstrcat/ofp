#include "ofp.h"

std::string aes_encrypt_cfb(const std::string& clearText, const std::string& _key, const std::string& _iv);

unsigned char keytables[8][48] = {
	0x67, 0x65, 0x79, 0x63, 0x78, 0x75, 0x65, 0xE8, 0x37, 0xD2, 0x26, 0xB6, 0x9A, 0x49, 0x5D, 0x21, 
	0xF6, 0xC5, 0x02, 0x03, 0x51, 0x5A, 0x2C, 0xE7, 0xD8, 0xC3, 0xE1, 0xF9, 0x38, 0xB7, 0xE9, 0x4C, 
	0x42, 0xF2, 0xD5, 0x39, 0x91, 0x37, 0xE2, 0xB2, 0x81, 0x3C, 0xD8, 0xEC, 0xDF, 0x2F, 0x4D, 0x72, 
	
	0x9E, 0x4F, 0x32, 0x63, 0x9D, 0x21, 0x35, 0x7D, 0x37, 0xD2, 0x26, 0xB6, 0x9A, 0x49, 0x5D, 0x21, 
	0xA3, 0xD8, 0xD3, 0x58, 0xE4, 0x2F, 0x5A, 0x9E, 0x93, 0x1D, 0xD3, 0x91, 0x7D, 0x9A, 0x32, 0x18, 
	0x38, 0x69, 0x35, 0x39, 0x91, 0x37, 0x41, 0x6B, 0x67, 0x41, 0x6B, 0xEC, 0xF2, 0x2F, 0x51, 0x9A, 
	
	0x89, 0x2D, 0x57, 0xE9, 0x2A, 0x4D, 0x8A, 0x97, 0x5E, 0x3C, 0x21, 0x6B, 0x7C, 0x9D, 0xE1, 0x89, 
	0xD2, 0x6D, 0xF2, 0xD9, 0x91, 0x37, 0x85, 0xB1, 0x45, 0xD1, 0x8C, 0x72, 0x19, 0xB8, 0x9F, 0x26, 
	0x51, 0x69, 0x89, 0xE4, 0xA1, 0xBF, 0xC7, 0x8B, 0x36, 0x5C, 0x6B, 0xC5, 0x7D, 0x94, 0x43, 0x91, 
	
	0x27, 0x82, 0x79, 0x63, 0x78, 0x72, 0x65, 0xEF, 0x89, 0xD1, 0x26, 0xB6, 0x9A, 0x49, 0x5A, 0x21, 
	0x82, 0xC5, 0x02, 0x03, 0x28, 0x5A, 0x2C, 0xE7, 0xD8, 0xC3, 0xE1, 0x98, 0x38, 0x3C, 0xE9, 0x4C, 
	0x42, 0x2D, 0xD5, 0x39, 0x91, 0x81, 0xE2, 0x23, 0x81, 0x3C, 0xD8, 0xEC, 0xDF, 0x2E, 0x4D, 0x72, 
	
	0x3C, 0x4A, 0x61, 0x8D, 0x9B, 0xF2, 0xE4, 0x27, 0x9D, 0xC7, 0x58, 0xCD, 0x53, 0x51, 0x47, 0xC3, 
	0x87, 0xB1, 0x3D, 0x29, 0x70, 0x9A, 0xC1, 0xBF, 0x23, 0x82, 0x27, 0x6C, 0x4E, 0x8D, 0xF2, 0x32, 
	0x59, 0xB7, 0xA8, 0xE9, 0x67, 0x26, 0x5E, 0x9B, 0xCA, 0xBE, 0x24, 0x69, 0xFE, 0x4A, 0x91, 0x5E, 
	
	0x1C, 0x32, 0x88, 0x82, 0x2B, 0xF8, 0x24, 0x25, 0x9D, 0xC8, 0x52, 0xC1, 0x73, 0x31, 0x27, 0xD3, 
	0xE7, 0x91, 0x8D, 0x22, 0x79, 0x91, 0x81, 0xCF, 0x23, 0x12, 0x17, 0x6C, 0x9E, 0x2D, 0xF2, 0x98, 
	0x32, 0x47, 0xF8, 0x89, 0xA7, 0xB6, 0xDE, 0xCB, 0xCA, 0x3E, 0x28, 0x69, 0x3E, 0x4A, 0xAA, 0xFE, 
	
	0x1E, 0x4F, 0x32, 0x23, 0x9D, 0x65, 0xA5, 0x7D, 0x37, 0xD2, 0x26, 0x6D, 0x9A, 0x77, 0x5D, 0x43, 
	0xA3, 0x32, 0xD3, 0xC3, 0xE4, 0x2F, 0x5A, 0x3E, 0x93, 0x1D, 0xD9, 0x91, 0x72, 0x9A, 0x32, 0x1D, 
	0x3F, 0x2A, 0x35, 0x39, 0x9A, 0x37, 0x33, 0x77, 0x67, 0x41, 0x55, 0xEC, 0xF2, 0x8F, 0xD1, 0x9A, 
	
	0x12, 0x2D, 0x57, 0xE9, 0x2A, 0x51, 0x8A, 0xFF, 0x5E, 0x3C, 0x78, 0x6B, 0x7C, 0x34, 0xE1, 0x89, 
	0xDD, 0x6D, 0xF2, 0xD9, 0x54, 0x37, 0x85, 0x67, 0x45, 0x22, 0x71, 0x72, 0x19, 0x98, 0x9F, 0xB0, 
	0x12, 0x69, 0x89, 0x65, 0xA1, 0x32, 0xC7, 0x61, 0x36, 0xCC, 0x88, 0xC5, 0xDD, 0x94, 0xEE, 0x91
};


//#pragma pack(1)

struct Info1{
	char prjname[46];
	qword unknownval;
	char reserved[4];
	char cpu[7];
	char flashtype[5];
	word hdr2entries;
	char prjinfo[32];
	word crc;
};

struct Hdr2{
	char name[32];
	qword start;
	qword length;
	qword enclength;
	char filename[32];
	qword crc;
};

String mtk_shuffle(String key, int keylength, String input, int inputlength)
{
	StringBuffer b;
	b.SetLength(inputlength);
	
	for(int i=0; i<inputlength; i++)
	{
		unsigned char k = key[i%keylength];
		unsigned char h = (((input[i]) & 0xF0) >> 4) | (16 * ((input[i]) & 0xF));
		
		b[i] = k ^ h;
	}
	
	String r(b);
	DUMPHEX(r);
	return r;
}

String mtk_shuffle2(String key, int keylength, String input, int inputlength)
{
	StringBuffer b;
	b.SetLength(inputlength);
	
	for(int i=0; i<inputlength; i++)
	{
		char tmp = key[i%keylength] ^ input[i];
		char d =((tmp & 0xF0) >> 4) | (16 * (tmp & 0xF));
		
		b[i] = d;
	}
	
	return ~b;
}

void getkey(int index,std::string& aeskey, std::string& aesiv)
{
	String obskey = String(&keytables[index][0],16);
//	DUMPHEX(obskey);
	String encaeskey = String(&keytables[index][0]+16,16);
//	DUMPHEX(encaeskey);
	String encaesiv = String(&keytables[index][0]+32,16);
//	DUMPHEX(encaesiv);
	
	aeskey = MD5String(mtk_shuffle2(obskey,16,encaeskey,16)).Left(16);
	aesiv = MD5String(mtk_shuffle2(obskey,16,encaesiv,16)).Left(16);
}

/*
def brutekey(rf):
    rf.seek(0)
    encdata=rf.read(16)
    for keyid in range(0,len(keytables)):
        aeskey, aesiv = getkey(keyid)
        data = aes_cfb(aeskey, aesiv, encdata, True)
        if data[:3]==b"MMM":
            return aeskey, aesiv
    print("Unknown key. Please ask the author for support :)")
    exit(0)
*/

bool brutekey(std::string encdata, std::string& sKey, std::string& sIv)
{
	int n = sizeof(keytables);

	for(int i=0; i<8; i++)
	{
		getkey(i,sKey,sIv);

		
		LOGHEXDUMP(encdata.c_str(),16);
		
		std::string sOut = aes_encrypt_cfb(encdata,sKey,sIv);

		String s = sOut;
		if(s.Left(3) == "MMM")
		{
			DUMP(sKey.c_str());
			DUMP(sIv.c_str());
			return true;
		}    		
	}
	
	RLOG("Unknown key. Please ask the author for support :)");
	return false;
}

void ofp::decfile(String fn)
{
	FileIn in(fn);
	if(in)
	{
		char* hdrkey = "geyixue";
		int64 filesize = in.GetSize();
		int hdrlength = 0x6c;
		
		while(!in.IsEof())
		{
			char b[16] = {0};
			in.Get(b,16);
			
			std::string aeskey,aesiv;
			if(!brutekey(std::string(b,16),aeskey,aesiv))
				break;
			
			in.Seek(filesize - hdrlength);
			
			char b_hdr[0x6c] = {0};
			in.Get(b_hdr,hdrlength);
			LOGHEXDUMP(b_hdr,hdrlength);
			
			String hdr = mtk_shuffle(hdrkey, strlen(hdrkey), b_hdr, hdrlength);
			Info1* pInfo = (Info1*)~hdr;
			LOGHEXDUMP(~hdr,hdrlength);
			
			String prjname(pInfo->prjname);	
			String prjinfo(pInfo->prjinfo);
			String cpu(pInfo->cpu);
			String flashtype(pInfo->flashtype);
			
						
			e_prjname.SetText(prjname);
			e_prjinfo.SetText(prjinfo);
			e_cpu.SetText(cpu);
			e_flashtype.SetText(flashtype);
			
			
			int hdr2length=pInfo->hdr2entries*0x60;
			in.Seek(filesize-hdr2length-hdrlength);
			
			StringBuffer b_hdr2;
			b_hdr2.SetLength(hdr2length);
			in.Get(b_hdr2,hdr2length);
			String hdr2 = mtk_shuffle(hdrkey, strlen(hdrkey), b_hdr2, hdr2length);
			
			for(int i=0; i<hdr2.GetLength(); i+=0x60)
			{
				String data(~hdr2+i,0x60);
				Hdr2* pHdr2 = (Hdr2*)~data;
				
				String name(pHdr2->name);
				String filename(pHdr2->filename);
				
				LOGHEXDUMP(data,0x60);
				
				grid.Add(name,filename,(int64)pHdr2->start,(int64)pHdr2->length,(int64)pHdr2->enclength);
			}	
		}
	}
}

void ofp::extracfile(String fn, String folder)
{	
	FileIn in(fn);
	if(in)
	{
		char* hdrkey = "geyixue";
		int64 filesize = in.GetSize();
		int hdrlength = 0x6c;
		
		while(!in.IsEof())
		{
			char b[16] = {0};
			in.Get(b,16);
			
			std::string aeskey,aesiv;
			if(!brutekey(std::string(b,16),aeskey,aesiv))
				break;
			
			in.Seek(filesize - hdrlength);
			
			char b_hdr[0x6c] = {0};
			in.Get(b_hdr,hdrlength);
			LOGHEXDUMP(b_hdr,hdrlength);
			
			String hdr = mtk_shuffle(hdrkey, strlen(hdrkey), b_hdr, hdrlength);
			Info1* pInfo = (Info1*)~hdr;
			LOGHEXDUMP(~hdr,hdrlength);
			
			String prjname(pInfo->prjname);	
			String prjinfo(pInfo->prjinfo);
			String cpu(pInfo->cpu);
			String flashtype(pInfo->flashtype);
			
			int hdr2length=pInfo->hdr2entries*0x60;
			in.Seek(filesize-hdr2length-hdrlength);
			
			StringBuffer b_hdr2;
			b_hdr2.SetLength(hdr2length);
			in.Get(b_hdr2,hdr2length);
			String hdr2 = mtk_shuffle(hdrkey, strlen(hdrkey), b_hdr2, hdr2length);
			
			for(int i=0; i<hdr2.GetLength(); i+=0x60)
			{
				String data(~hdr2+i,0x60);
				Hdr2* pHdr2 = (Hdr2*)~data;
				
				String name(pHdr2->name);
				String filename(pHdr2->filename);
				
				FileOut out;
				if(!out.IsOpen())
				{
					String path = AppendFileName(folder , filename);
					RealizePath(path);
					out.Open(path);
					
					ShowStatus(path);
				}
				if(pHdr2->enclength)
				{
					in.Seek(pHdr2->start);
					StringBuffer b;
					b.SetLength(pHdr2->enclength);
					in.Get(b,pHdr2->enclength);
					if(pHdr2->enclength % 16 != 0)
					{
						int n = 16-(pHdr2->enclength % 16);
						b.Cat(0,n);
					}
					std::string encData(~b,b.GetLength());
				//	LOGHEXDUMP(~b,b.GetLength());
					String sOut = aes_encrypt_cfb(encData,aeskey,aesiv);
					{
						// ??????????????????????????????
						
						int n = 16-(pHdr2->enclength % 16);
						sOut.TrimLast(n);
					}
					out.Put(sOut);
					int64 len = pHdr2->length;
					len -= pHdr2->enclength;
					
					while(len)
					{
						int size = 0x200000;
						if(len < size)
							size = len;
						
						StringBuffer data;
						data.SetLength(size);
						in.Get(data,size);
						len -= size;
						out.Put(~data,data.GetLength());
					}
				}
				out.Close();
			}
			ShowStatus(t_("write success!"));
		}
	}	
}

