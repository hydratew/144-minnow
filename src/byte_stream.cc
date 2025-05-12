#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {}

bool Writer::is_closed() const
{
  // Your code here.
  return closesign;
}

void Writer::push( string data )
{
  // Your code here.
  if (is_closed() || available_capacity() == 0 || data.empty()) {return;}
  if (available_capacity() < data.length()){
    data = data.substr(0,available_capacity());
  }
  buffer_.push_back(data);
  pushed_count += data.length();
  buffered_count += data.length();
  return;
}

void Writer::close()
{
  // Your code here.
  closesign = true;
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  return capacity_ - buffered_count;
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return pushed_count;
}

bool Reader::is_finished() const
{
  // Your code here.
  if (closesign && buffered_count == 0) {return true;}
  return false;
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return popped_count;
}

string_view Reader::peek() const
{
  // Your code here.
  if (buffer_.empty()) {return string_view{};} 
  else {
    const string& front_item = buffer_.front();
    const char* start_ptr = front_item.data() + cutdown_count;
    size_t remaining_size = front_item.size() - cutdown_count;
    return string_view(start_ptr, remaining_size);
  }
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  if (buffered_count < len || buffer_.empty()) {return;}
  popped_count += len;
  buffered_count -= len;
  /*Someting need to do*/
  while (len > 0 && len >= (buffer_.front().size() - cutdown_count))
  {
    len -= (buffer_.front().size() - cutdown_count);
    buffer_.pop_front();
    cutdown_count = 0;
  }
  if (len > 0){
    cutdown_count += len;
  }

}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return buffered_count;
}
