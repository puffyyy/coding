<template>
  <el-row class="warp">
    <el-col :span="24" class="warp-breadcrum" :loading="loading">
      <el-breadcrumb separator="/">
        <el-breadcrumb-item :to="{ path: '/home' }"
          ><b>首页</b></el-breadcrumb-item
        >
        <el-breadcrumb-item>设置</el-breadcrumb-item>
        <el-breadcrumb-item>个人信息</el-breadcrumb-item>
      </el-breadcrumb>
    </el-col>

    <el-col :span="24" class="warp-main">
      <el-form
        ref="form"
        :model="form"
        :rules="rules"
        label-width="80px"
        class="login-container"
      >
        <el-form-item label="用户名">
          <el-input v-model="form.userName"></el-input>
        </el-form-item>
        <el-form-item prop="identity" label="角色">
          <el-input v-model="form.identity" disabled></el-input>
        </el-form-item>
        <el-form-item prop="password" label="密码">
          <el-input v-model="form.password" disabled></el-input>
        </el-form-item>
        <el-form-item prop="email" label="邮箱">
          <el-input v-model="form.email"></el-input>
        </el-form-item>
        <el-form-item style="margin-left: 100px">
          <el-button type="primary" @click="handleSaveProfile"
            >修改并保存</el-button
          >
        </el-form-item>
      </el-form>
    </el-col>
  </el-row>
</template>

<script>
import API from "../../api/api_user";
import { bus } from "../../bus.js";

export default {
  data() {
    return {
      loading: false,
      form: {
        userId: "",
        userName: "",
        identity: "",
        password: "",
        email: "",
      },
      rules: {
        identity: [{ message: "请输入昵称", trigger: "blur" }],
        email: [
          { message: "请输入邮箱", trigger: "blur" },
          {
            type: "email",
            message: "请输入正确的邮箱地址",
            trigger: "blur,change",
          },
        ],
      },
    };
  },
  methods: {
    handleSaveProfile() {
      let that = this;
      that.$refs.form.validate((valid) => {
        if (valid) {
          that.loading = true;
          let user = localStorage.getItem("access-user");
          user = JSON.parse(user);
          console.log(user);
          user.userName = this.form.userName;
          user.email = this.form.email;
          user.password = this.form.password;
          API.changeProfile(user)
            .then(
              function (result) {
                that.loading = false;
                if (result && result.stateCode === 0) {
                  //修改成功
                  window.localStorage.setItem(
                    "access-user",
                    JSON.stringify(user)
                  );
                  bus.$emit("setIdentity", that.form.identity);
                  that.$message.success({
                    showClose: true,
                    message: "修改成功",
                    duration: 2000,
                  });
                } else {
                  that.$message.error({
                    showClose: true,
                    message: result.errmsg,
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
  mounted() {
    let user = localStorage.getItem("access-user");
    if (user) {
      user = JSON.parse(user);
      this.form.userName = user.userName;
      this.form.identity = user.identity || "";
      this.form.email = user.email || "";
      this.form.password = user.password || "";
      this.form.userId = user.userId || "";
    }
    this.form.password = this.form.password.replace(/./g, "*");
  },
};
</script>
</style>
<style lang="scss" scoped>
.login-container {
  /*box-shadow: 0 0px 8px 0 rgba(0, 0, 0, 0.06), 0 1px 0px 0 rgba(0, 0, 0, 0.02);*/
  -webkit-border-radius: 5px;
  border-radius: 40px;
  -moz-border-radius: 5px;
  background-clip: padding-box;
  margin: 160px auto;
  width: 500px;
  padding: 35px 35px 15px 35px;
  // background: #fff;
  border: 1px solid #d5e1e7;
  box-shadow: 0 0 25px #b8ebe2;

  background-image: linear-gradient(-225deg, #ee9aee 0%, #94ebe9 100%);

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
.warp-main {
  background-image: linear-gradient(-225deg, #f3e1f3 0%, #d7fffe 100%);
}
</style>