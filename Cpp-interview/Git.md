## Git 基础操作

#### 初始化仓库
- **命令**: `git init`
- **示例**: 初始化当前目录为Git仓库。
  ```bash
  git init
  ```

#### 克隆仓库
- **命令**: `git clone [url]`
- **常用参数**:
  
  - `--branch [branch_name]` 或 `-b [branch_name]`: 克隆指定分支。
- **示例**:
  - 克隆指定分支的仓库：
    ```bash
    git clone -b develop https://github.com/example/repo.git
    ```

#### 添加文件
- **命令**: `git add [file]`
- **常用参数**:
  - `.`: 添加当前目录下的所有更改。
  - `-A`: 添加当前项目中的所有更改。
- **示例**:
  - 添加当前目录下的所有文件和更改：
    ```bash
    git add .
    ```
  - 添加项目中的所有更改：
    ```bash
    git add -A
    ```

#### 提交更改
- **命令**: `git commit -m "[commit message]"`
- **常用参数**:
  - `-am "[message]"`: 添加所有已跟踪文件的更改并提交。
  - `--amend`: 修改上一次的提交信息。
- **示例**:
  - 添加并提交所有更改：
    ```bash
    git commit -am "Update files"
    ```
  - 修改上一次的提交信息：
    ```bash
    git commit --amend -m "Corrected commit message"
    ```

#### 查看状态
- **命令**: `git status`
- **示例**:
  - 查看工作目录和暂存区状态：
    ```bash
    git status
    ```

#### 推送更改
- **命令**: `git push [remote] [branch]`
- **常用参数**:
  
  - `--set-upstream` 或 `-u`: 对于首次推送的分支，设置上游分支。
- **示例**:
  - 推送本地分支到远程仓库，并设置上游分支：
    ```bash
    git push -u origin feature-branch
    ```

#### 拉取更新
- **命令**: `git pull [remote] [branch]`
- **常用参数**:
  
  - `--rebase`: 使用变基而不是合并来整合远程仓库的更改。
- **示例**:
  - 从远程仓库拉取更新，并使用rebase整合：
    ```bash
    git pull origin master --rebase
    ```

## 分支管理

- **切换分支**
  - `git checkout [branch_name]`: 切换到已存在的另一个分支。

- **创建并切换分支**
  - `git checkout -b [new_branch]`: 创建一个新分支并立即切换到该分支。

- **合并分支**
  - `git merge [branch_name]`: 将指定分支的更改合并到当前分支。

- **查看所有分支**
  - `git branch`: 列出本地所有分支。

- **删除分支**
  - `git branch -d [branch_name]`: 删除指定的本地分支。

- **强制删除未合并的分支**
  - `git branch -D [branch_name]`: 强制删除没有合并到任何分支的分支。

### 特定操作

- **回退到具体某个版本**
  - `git checkout [commit_hash]`: 切换到特定的提交版本。

- **修改最近的commit信息**
  - `git commit --amend -m "New commit message"`: 修改最后一次提交的信息。

- **撤销最近的几次提交**
  - `git revert [commit_hash]`: 生成一个新的提交，这个提交是用来撤销指定提交的更改的。
  - `git reset --hard [commit_hash]`: 将HEAD指向指定的提交，并舍弃该提交之后的所有更改。

## fetch和pull的区别

#### git fetch

- **作用**: `git fetch`命令会下载远程仓库的最新历史到本地仓库，但它不会修改工作目录的内容，也不会自动合并或更新你的当前工作。它允许你在合并更改到你的分支之前先审查这些更改。
- **场景**: 当你想要看看远程仓库中有哪些更新，但还不想将这些更新合并到你的本地分支时，`git fetch`是一个好选择。

#### git pull

- **作用**: `git pull`命令实际上是`git fetch`后面跟着`git merge FETCH_HEAD`的简写。`git pull`会从你指定的远程仓库获取最新的版本，并自动尝试合并到你当前的分支。
- **场景**: 当你已经准备好接受远程仓库中的更新，并且希望立即将这些更新合并到你的当前分支时，`git pull`是适用的。

#### 总结

- **更新本地库的方式**: `git fetch`仅下载远程仓库的数据到本地，不自动合并或修改当前工作。而`git pull`则会自动将远程更改合并到当前分支。
- **使用场景**: 使用`git fetch`时，你可以先查看更新，然后决定是否要合并这些更改到你的分支。`git pull`更适合当你信任这些更改，并希望立即将其并入你的工作时使用。