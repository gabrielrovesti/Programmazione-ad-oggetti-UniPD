vector<QWidget> fun(const vector<const QPaintDevice*>&v){
    vector<QWidget> ret;
    for(auto it = v.begin(); it!=v.end(); it++){
        auto w = dynamic_cast<const QWidget*>(*it);
        auto b = dynamic_cast<const QAbstractButton*>(*it);
        if(w && w->width() > 80) throw QString("TooBig");
        if(w && w->width() <=80 && w->hasFocus()) const_cast<QWidget*>(w)->clearFocus();
        if(b) const_cast<QAbstractButton*>(b)->setText("Button");
        if(w && !b) ret.push_back(*w);
    }
    return ret;
}