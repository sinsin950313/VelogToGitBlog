# Velog To Git Blog

## Keyword : Modern CPP(STL, Smart Pointer, Lambda, File System), File IO, Design Pattern(Strategy Pattern, Singleton Pattern)

![298268274-df1ac3d3-f72f-4984-89d0-ed3b5517f2df.PNG](https://postfiles.pstatic.net/MjAyNDAyMDlfMjYw/MDAxNzA3NDczODQzOTQ2.VHYPTxLdf4ai1NUGy_AgfX9J_w-kdylWW3O9fJGrjqIg.jE2VOaiIbt-ocYh_rx8UAypyddG88QqwwxGMCtmFmIog.PNG.sinsin63/298268274-df1ac3d3-f72f-4984-89d0-ed3b5517f2df.png?type=w580)

## 개요

Velog의 Posting을 Git Blog로의 Porting을 자동화하는 프로그램

Velog Posting을 Crawling하는 과정에서 누락된 정보나 부족한 정보를 수정하기 위해 작성했습니다.

Velog를 Crawling해서 다운로드 하는 프로그램은 이걸 사용했습니다. [Link](https://github.com/cjaewon/velog-backup)

## 기술 스택

- CPP

## 주요 기능

- Modern CPP(STL, Smart Pointer, Lambda, FileSystem)
- Smart Pointer를 이용한 메모리 관리
- File IO를 이용한 파일 입출력
- FileSystem을 이용한 파일 관리
- Lambda
- Strategy Pattern을 이용한 Input Parameter 처리
- Singleton Pattern을 이용한 Input Parameter 처리

## 사용법
cmd에서 Exe 파일 위치를 기준으로

```
a.out -c {CategoryFile} -s {SourceDirectory} -d {DestinationDirectory}
```

도움말
```
a.out -h
```

## CategoryFile
```
[Category, {Tag1, Tag2, ..., TagN}]
```
제가 사용하는 Jekyll Theme의 경우 Super Category와 Sub Category를 요구하는데 Super Category는 Development로 고정입니다.

CategoryFile에 작성되지 않은 Tag들은 Sub Category로 Non이 사용됩니다.

## Undefined
Crawler가 인식하지 못하는 Image나 Video가 있는 경우 Undefined로 치환하는 경우가 있습니다.
Undefined처리된 Post들은 "Undefined Log List.txt" 파일에 따로 분리하여 사용자가 직접 확인할 수 있도록 분류했습니다.

## 세부사항

[Velog To Git Blog](https://www.notion.so/Velog-To-Git-Blog-b38c7e3e87634f36a856837f7c1850dd?pvs=21)
