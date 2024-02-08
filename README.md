![VelogToGitBlog](https://github.com/sinsin950313/VelogToGitBlog/assets/40855235/6e268f27-0147-4120-b3d1-be60a966a32c)

# Velog Posting을 Github Blog로 Porting하기
Velog Crawling해서 다운로드 하는 프로그램은 이걸 사용했습니다.
<br>
https://github.com/cjaewon/velog-backup

다운로드한 포스트들을 사용하는 Jekyll Theme에 맞도록 약간 수정을 하는 프로그램입니다.

제가 사용하는 Jekyll Theme 입니다.
<br>
https://chirpy.cotes.page/

## 기술 스택
- CPP
- File IO
- FileSystem

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
