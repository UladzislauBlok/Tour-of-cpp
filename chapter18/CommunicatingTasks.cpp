// • future and promise for returning a value from a task spawned on a separate thread
// • packaged_task to help launch tasks and connect up the mechanisms for returning a result
// • async() for launching of a task in a manner very similar to calling a function

void f(promise<X>& px) // a task: place the result in px
{
    // ...
    try {
        X res;
        // ... compute a value for res ...
        px.set_value(res);
    }
    catch (...) { // oops: couldn’t compute res
        px.set_exception(current_exception()); // pass the exception to the future’s thread
    }
}

void g(future<X>& fx) // a task: get the result from fx
{
    // ...
    try {
        X v = fx.get(); // if necessary, wait for the value to get computed
        // ... use v ...
    }
    catch (...) { // oops: someone couldn’t compute v
        // ... handle error ...
    }
}

double accum(vector<double>::iterator beg, vector<double>::iterator end, double init)
// compute the sum of [beg:end) starting with the initial value init
{
    return accumulate(&*beg,&*end,init);
}
double comp2(vector<double>& v)
{
    packaged_task pt0 {accum}; // package the task (i.e., accum)
    packaged_task pt1 {accum};
    future<double> f0 {pt0.get_future()}; // get hold of pt0’s future
    future<double> f1 {pt1.get_future()}; // get hold of pt1’s future
    double* first = &v[0];
    thread t1 {move(pt0),first,first+v.size()/2,0}; // start a thread for pt0
    thread t2 {move(pt1),first+v.size()/2,first+v.size(),0}; // start a thread for pt1
    // ...
    return f0.get()+f1.get(); // get the results
}

double comp4(vector<double>& v)
// spawn many tasks if v is large enough
{
    if (v.size()<10'000) // is it worth using concurrency?
        return accum(v.begin(),v.end(),0.0);
    auto v0 = &v[0];
    auto sz = v.size();
    auto f0 = async(accum,v0,v0+sz/4,0.0); // first quarter
    auto f1 = async(accum,v0+sz/4,v0+sz/2,0.0); // second quarter
    auto f2 = async(accum,v0+sz/2,v0+sz*3/4,0.0); // third quarter
    auto f3 = async(accum,v0+sz*3/4,v0+sz,0.0); // fourth quarter
    return f0.get()+f1.get()+f2.get()+f3.get(); // collect and combine the results
}

//Stopping a thread
atomic<int> result = -1; // put a resulting index here
template<class T> struct Range { T* first; T last; }; // a way of passing a range of Ts
void find(stop_token tok, const string* base, const Range<string> r, const string target)
{
    for (string* p = r.first; p!=r.last && !tok.stop_requested(); ++p)
        if (match(*p, target)) { // match() applies some matching criteria to the two strings
            result = p - base; // the index of the found element
            return;
        }
}
// Here, !tok.stop_requested() tests whether some other thread has requested this thread to terminate.
// Here is a trivial find_any() that spawns just two threads running find():
void find_all(vector<string>& vs, const string& key)
{
    int mid = vs.size()/2;
    string* pvs = &vs[0];
    stop_source ss1{};
    jthread t1(find, ss1.get_token(), pvs, Range{pvs,pvs+mid}, key); // first half of vs
    stop_source ss2{};
    jthread t2(find, ss2.get_token(), pvs, Range{pvs+mid,pvs+vs.size()} , key); // second half of vs
    while (result == -1)
        this_thread::sleep_for(10ms);
    ss1.request_stop(); // we have a result: stop all threads
    ss2.request_stop();
    // ... use result ...
}
// The stop_sources produces the stop_tokens through which requests to stop are communicated to threads.

