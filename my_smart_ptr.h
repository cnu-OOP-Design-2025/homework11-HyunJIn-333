#pragma once


template<typename T>
class my_shared_ptr {
private:
    T* ptr;
    size_t* refCount;

public:
    // 생성자
    explicit my_shared_ptr(T* p = nullptr) : ptr(p), refCount(new size_t(1)) {}

    // 복사 생성자
    my_shared_ptr(const my_shared_ptr& other) : ptr(other.ptr), refCount(other.refCount) {
        ++(*refCount); // 참조 카운트 증가
    }

    // 대입 연산자
    my_shared_ptr& operator=(const my_shared_ptr& other) {
        if (this != &other) {
            release();          // 기존 자원 정리
            ptr = other.ptr;    // 포인터 공유
            refCount = other.refCount;
            ++(*refCount);      // 참조 카운트 증가
        }
        return *this;
    }

    // 소멸자
    ~my_shared_ptr() { release(); }

    // 참조 해제
    void release() {
        if (refCount && --(*refCount) == 0) { // 마지막 참조이면 삭제
            delete ptr;
            delete refCount;
        }
    }

    // 접근 연산자
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // 참조 카운트 확인
    size_t use_count() const { return *refCount; }

    // get() 기능: raw 포인터 리턴
    T* get() const { return ptr; }

    // reset() 기능: 새로운 포인터로 교체
    void reset(T* p = nullptr) {
        release();
        ptr = p;
        refCount = new size_t(1);
    }
};


template <typename T>
class my_unique_ptr {
private:
    T* ptr;
public:
    // 생성자
    explicit my_unique_ptr(T* p = nullptr) : ptr(p) {}

    // 소멸자
    ~my_unique_ptr() {
        delete ptr;
    }

    // 복사 금지
    my_unique_ptr(const my_unique_ptr&) = delete;
    my_unique_ptr& operator=(const my_unique_ptr&) = delete;

    // 이동 생성자: other가 관리하는 자원의 소유권을 가져옴 
    my_unique_ptr(my_unique_ptr&& other) noexcept: ptr(nullptr) {
        ptr = other.ptr;       // 소유권 이동
        other.ptr = nullptr;   // 원본 비움
    }

    // 이동 대입 연산자: 기존 unique_ptr이 관리하던 자원을 해제하고, 다른 unique_ptr가 관리하는 자원의 소유권을 가져옴 
    my_unique_ptr& operator=(my_unique_ptr&& other) noexcept {
        if (this != &other) {
            delete ptr;        // 기존 자원 삭제
            ptr = other.ptr;   // 새 소유권
            other.ptr = nullptr;
        }
        return *this;
    }

    // 포인터 접근
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // get() 메서드
    T* get() const { return ptr; }

    // release() 메서드: 내부 포인터를 반환하고, ptr은 nullptr로 초기화
    T* release() {
        T* temp = ptr;   // 현재 포인터 저장
        ptr = nullptr;   // 소유권 포기
        return temp;     // raw 포인터 반환
    }

    // reset() 메서드
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};
