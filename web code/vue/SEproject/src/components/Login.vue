<template>
  <el-form
    ref="AccountFrom"
    :model="account"
    :rules="rules"
    label-position="left"
    label-width="0px"
    class="demo-ruleForm login-container"
  >
    <h3 class="title">图书馆信息管理系统</h3>
    <el-form-item prop="userName" style="width: 80%; margin-left: 30px">
      <el-input
        class="input"
        type="text"
        v-model="account.userName"
        auto-complete="off"
        placeholder="账号"
      ></el-input>
    </el-form-item>
    <el-form-item prop="password" style="width: 80%; margin-left: 30px">
      <el-input
        type="password"
        v-model="account.password"
        auto-complete="off"
        placeholder="密码"
      ></el-input>
    </el-form-item>
    <el-checkbox
      v-model="checked"
      checked
      class="remember"
      style="margin-left: 35px"
    >
      记住密码</el-checkbox
    >
    <tr></tr>
    <router-link to="/register" style="margin-left: 80px"
      >还没有账号，注册一下？</router-link
    >
    <el-form-item
      style="
        width: 70%;
        margin-left: 45px;
        border-radius: 15px;
        margin-top: 20px;
      "
    >
      <el-button
        type="primary"
        style="
          width: 100%;
          border-radius: 15px;
          background-image: linear-gradient(to top, #a8edea 0%, #fed6e3 100%);
        "
        @click.native.prevent="handleLogin"
        :loading="loading"
        >登录</el-button
      >
    </el-form-item>
  </el-form>
</template>

<script>
import API from "../api/api_user";

export default {
  data() {
    return {
      loading: false,
      account: {
        userName: "dq",
        password: "1",
      },
      rules: {
        userName: [
          { required: true, message: "请输入账号", trigger: "blur" },
          //{ validator: validaePass }
        ],
        password: [
          { required: true, message: "请输入密码", trigger: "blur" },
          //{ validator: validaePass2 }
        ],
      },
      checked: true,
    };
  },
  methods: {
    handleLogin() {
      let that = this;
      this.$refs.AccountFrom.validate((valid) => {
        if (valid) {
          this.loading = true;
          let loginParams = {
            userName: this.account.userName,
            password: this.account.password,
          };
          console.log(loginParams);
          API.login(loginParams)
            .then(
              function (result) {
                that.loading = false;
                if (result && result.userId) {
                  localStorage.setItem("access-user", JSON.stringify(result));
                  localStorage.setItem("identity", result.identity);
                  that.$router.push({ path: "/home" });
                } else {
                  console.log(result);
                  that.$message.error({
                    showClose: true,
                    message: result.errmsg || "登录失败",
                    duration: 2000,
                  });
                }
              },
              function (err) {
                that.loading = false;
                that.$message.error({
                  showClose: true,
                  message: err.toString(),
                  duration: 2000,
                });
              }
            )
            .catch(function (error) {
              that.loading = false;
              console.log(error);
              that.$message.error({
                showClose: true,
                message: "请求出现异常",
                duration: 2000,
              });
            });
        }
      });
    },
  },
};
</script>
<style>
body {
  background: #dfe9fb;
  height: 780px;
  background-image: linear-gradient(
    -225deg,
    #2cd8d5 0%,
    #c5c1ff 56%,
    #ffbac3 100%
  );
}
</style>
<style lang="scss" scoped>
.login-container {
  /*box-shadow: 0 0px 8px 0 rgba(0, 0, 0, 0.06), 0 1px 0px 0 rgba(0, 0, 0, 0.02);*/
  -webkit-border-radius: 5px;
  border-radius: 40px;
  -moz-border-radius: 5px;
  background-clip: padding-box;
  margin: 160px auto;
  width: 350px;
  padding: 35px 35px 15px 35px;
  // background: #fff;
  border: 1px solid #d5e1e7;
  box-shadow: 0 0 25px #b8ebe2;

  background-image: linear-gradient(-225deg, #f3e1f3 0%, #d7fffe 100%);

  background: -ms-linear-gradient(top, #ace, #00c1de); /* IE 10 */
  background: -moz-linear-gradient(top, #ace, #00c1de); /*火狐*/
  background: -webkit-gradient(
    linear,
    0% 0%,
    0% 100%,
    from(#ace),
    to(#00c1de)
  ); /*谷歌*/
  background: -webkit-linear-gradient(
    top,
    #ace,
    #00c1de
  ); /*Safari5.1 Chrome 10+*/
  background: -o-linear-gradient(top, #ace, #00c1de); /*Opera 11.10+*/

  .title {
    margin: 0px auto 40px auto;
    text-align: center;
    color: #505458;
  }
  .remember {
    margin: 0px 0px 35px 0px;
  }
}
.input {
  text-align: center;
  border-radius: 5px;
}
</style>