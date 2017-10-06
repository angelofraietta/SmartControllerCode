
class  ActiveFileBlock
{
public:
	ActiveFileBlock ():_block_num(0){}
	virtual ~ActiveFileBlock();
	virtual void WriteBlock(const BYTE* data, unsigned num_bytes, unsigned block_num) {}
	virtual unsigned ReadBlock (BYTE* ret_data, unsigned num_bytes){return 0;}
  unsigned FileLength();
protected:
	unsigned _block_num;
	FILE* _fp;
};

unsigned ActiveFileBlock::FileLength()
{
	struct stat statbuf;
	fstat(fileno(_fp), &statbuf);
	return statbuf.st_size;
}

class ActiveFileBlockWriter :public ActiveFileBlock
{
public:
	ActiveFileBlockWriter (const char* filename);
	void WriteBlock(const BYTE* data, unsigned num_bytes, unsigned block_num);

};

class ActiveFileBlockReader :public ActiveFileBlock
{
public:
	ActiveFileBlockReader (const char* filename);
	unsigned ReadBlock (BYTE* ret_data, unsigned num_bytes);

private:

};

