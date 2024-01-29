#ifndef CONTAINER_OUTPUT
#define CONTAINER_OUTPUT
#include<ostream>

enum ContainerElementType{
    STRING,
    CHAR,
    BOOL,
    OTHER
};
template<typename T>
struct IsPair: std::false_type{};

template<typename T,typename U>
struct IsPair<std::pair<T,U>> : std::true_type{};

template<typename T>
struct HasOutputFunction{
    template<class U>
    static auto output(U *ptr)
    -> decltype(std::declval<std::ostream&>()<<*ptr,std::true_type());

    template<class U>
    static std::false_type output(...);

    static constexpr bool value = decltype(output<T>(nullptr))::value;
};




template<typename T>
void ouputValue(const T& value,int type,std::ostream&os){
    switch (type)
    {
    case STRING:{
        os<<"\""<<value<<"\"";
        break;
    }
    case CHAR:{
        os<<'\''<<value<<"\'";
        break;
    }
    
    case OTHER:{
        os<<value;
        break;
    }

    case BOOL:{
        if constexpr (std::is_same_v<T, bool>) {  
            os << (value ? "true" : "false");
        }
        break;
    }
    default:
        break;
    }
}

template<typename T>
ContainerElementType detectElementType (const T&value){
    using valueType = std::decay_t<decltype(value)>;
    constexpr int isChar = std::is_same<valueType,char>::value;
    constexpr int isString = std::is_same<valueType,const char*>::value||
                         std::is_same<valueType,std::string>::value||
                         std::is_same<valueType,char*>::value;
    if(isChar){
        return CHAR;
    }else if(isString){
        return STRING;
    }
    if constexpr (std::is_same<valueType,char>::value){
        return CHAR;
    }else if constexpr(std::is_same<valueType,bool>::value){
        return BOOL;
    }else if constexpr(std::is_same<valueType,const char*>::value||
                         std::is_same<valueType,std::string>::value||
                         std::is_same<valueType,char*>::value){
        return STRING;
    }
    return OTHER;
}
template<typename T, typename Cont>
auto outputKeyValuePair(std::ostream&os, const T &value, const Cont &) ->
    typename std::enable_if<IsPair<typename Cont::value_type>::value,bool>::type{
    
    int firstType = detectElementType(value.first);
    int secondType = detectElementType(value.second);

    ouputValue(value.first,firstType,os);
    os<<" : ";
    ouputValue(value.second,secondType,os);
    return true;
}

template<typename T>
void outputNonKeyValuePair(std::ostream&os,const T& value){
    int valueType = detectElementType(value);
    ouputValue(value,valueType,os);
}

template<typename T, typename U>
std::ostream& operator<<(std::ostream &os, const std::pair<T,U>&pair){
    os<<'('<<pair.first<<","<<pair.second<<')';
    return os;
}


template<typename T, typename = std::enable_if_t<!HasOutputFunction<T>::value>>
auto operator<<(std::ostream& os,const T&container)->decltype(container.begin(),container.end(),os){
    os << "{";
    if(!container.empty()){
        bool isFirstElement = true;
        for(const auto& element:container){
            if(!isFirstElement){
                os<<", ";
            }else{
                isFirstElement=false;
            }
            if constexpr (IsPair<typename T::value_type>::value){
                outputKeyValuePair(os,element,container);
            }else{
                outputNonKeyValuePair(os,element);
            }
            
        }
        
    }
    os<<" }";
    return os;
}

#endif 